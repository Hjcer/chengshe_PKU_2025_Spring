
#include"picture.h"
#include<iostream>
#include<fstream>

using namespace std;
char bbyte;



int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " <image_file>" << endl;
        return 1;
    }

    std ::string input_file = argv[1];
    std ::string output_file = argv[2];
    picture p(input_file);
    p.rotate("left", 90, output_file);
    return 0;
}