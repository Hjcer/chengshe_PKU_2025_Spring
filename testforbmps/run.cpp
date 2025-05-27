#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {


    std::string input_dir = "bmps";
    std::string output_dir = "output"; // 输出文件夹
    std::string a_exe = "demo.exe";       // 假设 a.exe 在当前目录下

    // 创建输出文件夹
    if (!fs::exists(output_dir)) {
        fs::create_directory(output_dir);
    }

    // 遍历输入文件夹中的所有文件
    for (const auto& entry : fs::directory_iterator(input_dir)) {
        const fs::path& input_file = entry.path();
        if (fs::is_regular_file(input_file)) {
            // 生成输出文件名
            std::string output_file = output_dir + "/" + input_file.filename().string();

            // 调用 a.exe 处理文件
            std::string command = a_exe + " \"" + input_file.string() + "\" \"" + output_file + "\"";
            std::cout << "Processing: " << input_file.filename() << std::endl;
            std::system(command.c_str());
        }
    }

    std::cout << "Processing completed." << std::endl;
    return 0;
}

