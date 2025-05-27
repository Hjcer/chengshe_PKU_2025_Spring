#ifndef PICTURE_H
#define PICTURE_H
#include<string>
#include<vector>

class picture
{
private:
    int size;
    int viaaddr;
    int width;
    int height;
    short per_bit_pix;
    int iszipped;
    int information_head_size ;
    int biClrUsed;
    std::vector<std::vector<std::vector<char>>>the_data;
    std::vector<std::vector<char>>the_data16;
    std::vector<std::vector<char>>color_bit_map;
    std::vector<char>information_head;
    
    
public:
    picture(std::string FILEPATH);
    void rotate(std::string direction, int angle, std::string OUTPATH);
    ~picture();
};
#endif
