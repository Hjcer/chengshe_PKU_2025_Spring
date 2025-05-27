#include "picture.h"
#include <iostream>
#include <fstream>
#include <string>

picture::picture(std::string FilEPATH)
{
    std::ifstream infile(FilEPATH, std::ios::binary);
    infile.seekg(2, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->size)), sizeof(this->size));
    infile.seekg(0xa, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->viaaddr)), sizeof(this->viaaddr));
    infile.seekg(0xe, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->information_head_size)), sizeof(this->information_head_size));
    infile.seekg(0x12, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->width)), sizeof(this->width));
    infile.seekg(0x16, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->height)), sizeof(this->height));
    infile.seekg(0x1c, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->per_bit_pix)), sizeof(this->per_bit_pix));
    infile.seekg(0x1e, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->iszipped)), sizeof(this->iszipped));
    infile.seekg(0x2e, std::ios::beg);
    infile.read(reinterpret_cast<char *>(&(this->biClrUsed)), sizeof(this->biClrUsed));
    infile.seekg(0, std::ios::beg);
    this->information_head.resize(this->information_head_size + 14);
    infile.read(this->information_head.data(), this->information_head_size + 14);

    if (this->per_bit_pix < 24)
    {
        this->color_bit_map.resize(1 << this->per_bit_pix, std::vector<char>(4));
        // 当文件为8位深度的时候, 颜色的信息是存储在调色板里的, 因此, 这时候我们需要从调色板里读取颜色信息
        infile.seekg(0x36, std::ios::beg);
        // 我们有biClrUsed个颜色, 每个颜色4个字节, 因此我们需要读取biClrUsed * 4个字节
        for (int i = 0; i < this->biClrUsed; i++)
        {
            char b[4];
            infile.read(b, 4);
            this->color_bit_map[i][0] = b[2]; // R
            this->color_bit_map[i][1] = b[1]; // G
            this->color_bit_map[i][2] = b[0]; // B
            this->color_bit_map[i][3] = b[3]; // A
        }
        // 此时, 每一个像素都是4个字节, 因此不需要考虑对齐, 直接读取就可以了
        // 然后, 我们需要读取一下像素信息, 在小于24位的情况下, 像素中的信息是一个一个字节大小的, 也就是一个像素的值是一个字节, 这个字节的值就是调色板中的索引值, 我们需要根据这个索引值来获取颜色信息
        this->the_data16.resize(this->height, std::vector<char>(this->width));
        infile.seekg(this->viaaddr, std::ios::beg);
        // 当文件为8位深度的时候, 像素信息是直接存到像素里的, 因此, 这时候我们需要直接从像素里读取1个字节, 关键的一点是考虑对齐
        for (int i = this->height - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->width; j++)
            {
                char b[1];
                infile.read(b, 1);
                this->the_data16[i][j] = b[0]; // 读取像素值
            }
            // 对齐, 每行的字节数必须是4的倍数, 因此需要补齐
            int padding = (4 - (this->width) % 4) % 4;
            infile.seekg(padding, std::ios::cur);
        }
    }
    else
    {
        this->color_bit_map.resize(0);
        if (this->per_bit_pix == 24)
        {
            this->the_data.resize(this->height, std::vector<std::vector<char>>(this->width, std::vector<char>(3)));
            infile.seekg(this->viaaddr, std::ios::beg);
            // 当文件为24位深度的时候, 像素信息是直接存到像素里的, 因此, 这时候我们需要直接从像素里读取3个字节, 关键的一点是考虑对齐
            for (int i = this->height - 1; i >= 0; i--)
            {
                for (int j = 0; j < this->width; j++)
                {
                    char b[3];
                    infile.read(b, 3);
                    //作反色处理
                    this->the_data[i][j][0] = 255 - b[2]; // R
                    this->the_data[i][j][1] = 255 - b[1]; // G
                    this->the_data[i][j][2] = 255 - b[0]; // B
                }
                // 对齐, 每行的字节数必须是4的倍数, 因此需要补齐
                int padding = (4 - (this->width * 3) % 4) % 4;
                infile.seekg(padding, std::ios::cur);
            }
        }
        else if (this->per_bit_pix == 32)
        {
            this->the_data.resize(this->height, std::vector<std::vector<char>>(this->width, std::vector<char>(4)));
            infile.seekg(this->viaaddr, std::ios::beg);
            // 当文件为32位深度的时候, 像素信息是直接存到像素里的, 因此, 这时候我们需要直接从像素里读取4个字节, 关键的一点是考虑对齐
            for (int i = this->height - 1; i >= 0; i--)
            {
                for (int j = 0; j < this->width; j++)
                {
                    char b[4];
                    infile.read(b, 4);
                    //作反色处理
                    this->the_data[i][j][0] = 255 - b[2]; // R
                    this->the_data[i][j][1] = 255 - b[1]; // G
                    this->the_data[i][j][2] = 255 - b[0]; // B
                    this->the_data[i][j][3] = b[3];       // A
                }
                // 对齐, 每行的字节数必须是4的倍数, 因此需要补齐
                int padding = (4 - (this->width * 4) % 4) % 4;
                infile.seekg(padding, std::ios::cur);
            }
        }
    }
}
picture ::~picture()
{
    // 析构函数, 释放内存
    this->size = 0;
    this->viaaddr = 0;
    this->width = 0;
    this->height = 0;
    this->per_bit_pix = 0;
    this->iszipped = 0;
    this->information_head_size = 0;
    this->biClrUsed = 0;
    this->the_data.clear();
    this->the_data16.clear();
    this->color_bit_map.clear();
    this->information_head.clear();
}

void picture::rotate(std::string direction, int angle, std::string OUTPATH)
{
    std::ofstream outfile(OUTPATH, std::ios::binary);
    if (!outfile.is_open())
    {
        std::cout << "open file error" << std::endl;
        return;
    }

    // 首先, 我们需要将文件头写入到文件中, 这个文件头是固定的, 因为我们只需要修改像素信息, 而不需要修改文件头信息
    // 对文件头的长宽进行重新更改
    std::vector<char> file_head(this->viaaddr);
    std::copy(this->information_head.begin(), this->information_head.end(), file_head.begin());

    // 对文件头的长宽进行重新更改
    file_head[18] = this->information_head[22];
    file_head[19] = this->information_head[23];
    file_head[20] = this->information_head[24];
    file_head[21] = this->information_head[25];
    file_head[22] = this->information_head[18];
    file_head[23] = this->information_head[19];
    file_head[24] = this->information_head[20];
    file_head[25] = this->information_head[21];

    // 变换水平&竖直分辨率
    file_head[38] = this->information_head[42];
    file_head[39] = this->information_head[43];
    file_head[40] = this->information_head[44];
    file_head[41] = this->information_head[45];
    file_head[42] = this->information_head[38];
    file_head[43] = this->information_head[39];
    file_head[44] = this->information_head[40];
    file_head[45] = this->information_head[41];

    // 重新计算文件大小:
    // 像素数据大小需要加上补齐的像素

    int size_pixel = 0;
    if (this->per_bit_pix < 24)
    {
        size_pixel = this->width * this->height + (4 - (this->height % 4)) % 4 * this->width;
    }
    else
    {
        size_pixel = this->width * this->height * (this->per_bit_pix / 8) + ((4 - (this->height * (this->per_bit_pix / 8)) % 4) % 4) * this->width;
    }

    int total_new_size = this->viaaddr + size_pixel;
    char *p = reinterpret_cast<char *>(&total_new_size);
    for (int i = 0; i < 4; i++)
    {
        file_head[2 + i] = p[i];
    }

    // 旋转像素位
    if (this->per_bit_pix < 24)
    {
        std::vector<std::vector<char>> new_data(this->width, std::vector<char>(this->height));
        if (direction == "left")
        {

            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[j][this->height - 1 - i] = this->the_data16[i][j];
                }
            }
        }
        else if (direction == "right")
        {

            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[this->width - 1 - j][i] = this->the_data16[i][j];
                }
            }
        }

        // 将新的像素数据写入到文件中
        outfile.write(file_head.data(), file_head.size());
        outfile.seekp(this->viaaddr, std::ios::beg);
        for (int i = this->width - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->height; j++)
            {
                char b[1];
                b[0] = new_data[i][j]; // 读取像素值
                outfile.write(b, 1);
            }
            // 对齐, 每行的字节数必须是4的倍数, 因此需要补齐
            int padding = (4 - (this->width) % 4) % 4;
            char b[3] = {0};
            outfile.write(b, padding);
            outfile.seekp(padding, std::ios::cur);
        }
        
    }
    // 当大于等于24位的时候, 直接对像素位进行旋转
    else if (this->per_bit_pix == 24)
    {
        std::vector<std::vector<std::vector<char>>> new_data(this->width, std::vector<std::vector<char>>(this->height, std::vector<char>(3)));
        if (direction == "left")
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[j][this->height - 1 - i] = this->the_data[i][j];
                }
            }
        }
        else if (direction == "right")
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[this->width - 1 - j][i] = this->the_data[i][j];
                }
            }
        }

        // 将新的像素数据写入到文件中
        outfile.write(file_head.data(), file_head.size());
        outfile.seekp(this->viaaddr, std::ios::beg);
        for (int i = this->width - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->height; j++)
            {
                char b[3];
                b[0] = new_data[i][j][2]; // R
                b[1] = new_data[i][j][1]; // G
                b[2] = new_data[i][j][0]; // B
                outfile.write(b, 3);
            }
            // 对齐, 每行的字节数必须是4的倍数, 因此需要补齐
            int padding = (4 - (this->height * 3) % 4) % 4;
            char b[3] = {0};
            outfile.write(b, padding);
        }
        
    }
    else if (this->per_bit_pix == 32)
    {
        std::vector<std::vector<std::vector<char>>> new_data(this->width, std::vector<std::vector<char>>(this->height, std::vector<char>(4)));
        if (direction == "left")
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[j][this->height - 1 - i] = this->the_data[i][j];
                }
            }
        }
        else if (direction == "right")
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    new_data[this->width - 1 - j][i] = this->the_data[i][j];
                }
            }
        }
        // 将新的像素数据写入到文件中
        outfile.write(file_head.data(), file_head.size());
        outfile.seekp(this->viaaddr, std::ios::beg);
        for (int i = this->width - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->height; j++)
            {
                char b[4];
                b[0] = new_data[i][j][2]; // R
                b[1] = new_data[i][j][1]; // G
                b[2] = new_data[i][j][0]; // B
                b[3] = new_data[i][j][3]; // A
                outfile.write(b, 4);
            }
        }
    }

    outfile.close();
    std::cout << "rotate end" << std::endl;
}