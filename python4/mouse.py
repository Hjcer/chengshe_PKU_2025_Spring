import pyautogui
import time
import keyboard

def control_mouse():
    # 获取屏幕分辨率
    screen_width, screen_height = pyautogui.size()
    print(f"屏幕分辨率: {screen_width}x{screen_height}")
    
    # 确保鼠标不会移动到屏幕边缘导致程序崩溃
    pyautogui.FAILSAFE = True
    
    try:
        while True:
            print("打开浏览器菜单")
            pyautogui.moveTo(2469, 80, duration=0.2)
            print("点击鼠标左键：")
            pyautogui.click()
            print("打开隐私模式")
            pyautogui.moveTo(2450, 165, duration=0.2)
            pyautogui.click()
            print("复制网址")
            pyautogui.moveTo(1789, 72, duration=0.2)
            pyautogui.rightClick()
            pyautogui.moveTo(1883, 300)
            pyautogui.click()
            keyboard.press_and_release('enter')
            time.sleep(1)
            pyautogui.moveTo(2098, 867, duration=0.2)
            keyboard.press_and_release('pagedown')
            pyautogui.moveTo(1226, 751, duration=0.1)
            time.sleep(0.5)
            pyautogui.click()
            time.sleep(1)
            pyautogui.moveTo(2549, 8, duration= 0.1)
            pyautogui.click()
            
    
    except pyautogui.FailSafeException:
        print("检测到鼠标移动到屏幕左上角，程序已安全退出。")
    
    except Exception as e:
        print(f"发生错误: {e}")

if __name__ == "__main__":
    print("程序将在2秒后开始...")
    time.sleep(2)
    control_mouse()

