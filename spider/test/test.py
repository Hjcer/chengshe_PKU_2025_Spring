import asyncio
from urllib.parse import unquote
import re
import pyppeteer
from bs4 import BeautifulSoup
import os
import requests


chrome_path = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"

base_url = "https://cn.bing.com/dict/search?q="

async def get_word_html(word):
    url = base_url + word
    browser = await pyppeteer.launch(headless=True, executablePath=chrome_path)  # headless=True 表示无头浏览器
    page = await browser.newPage()
    await page.setUserAgent(
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3")
    await page.goto(url)

    # 得到当前页面的 html
    html = await page.content()
    await browser.close()
    
    soup = BeautifulSoup(html, "html.parser")

    syn_div = soup.find("div", id = "synoid")

    syn_words = []

    if syn_div:
        for span in syn_div.find_all("span", class_ = "p1-4 b_alink"):
            syn_words.append(span.get_text())

    img_area = soup.find("div", class_="img_area")
    if img_area:
        img_tag = img_area.find("img")
        if img_tag and img_tag.has_attr("src"):
            img_url = img_tag["src"]
            try:
                img_data = requests.get(img_url).content
                img_path = os.path.join(os.getcwd(), f"{word}.png")
                with open(img_path, "wb") as f:
                    f.write(img_data)
                #print(f"🖼️ 图片已保存：{img_path}")
            except Exception as e:
                print(f"下载图片失败：{e}")
        else:
            print("没有找到有效的 <img> 标签")
    else:
        print("未找到图片区域")
    
    return syn_words



if __name__ == "__main__":


    file = open("words.txt", "r", encoding="utf-8")
    lines = file.readlines()
    file.close()

    target_file = open("result.txt", "w", encoding="utf-8")

    for word in lines:
        target_file.write("$" + word)
        alist = asyncio.run(get_word_html(word.strip()))
        for item in alist:
            target_file.write(item + "\n")
    
    target_file.close()
        

    
