#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {
    std::string source;
    source = "#--[include]\n\n#--\ndef int a = 1;\ndef int b = 2;\nexit(20);";

    if (source.substr(0, 12) != "#--[include]") {
        std::cerr << "Invalid code header";
    }
    source.erase(0, 12);
    
    int endHeaderpos;
    endHeaderpos = source.find("#--\n", 0);
    if (endHeaderpos == -1) {
        std::cerr << "No end of header found" << std::endl;
    }
    source.erase(0,endHeaderpos + 4);
    std::cout << source << std::endl;

    return 0;
}