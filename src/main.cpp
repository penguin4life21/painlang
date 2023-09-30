#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "token.hpp"

#include "utils/tokentypetostring.hpp"

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string source;
    source = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    file.close();

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

    std::vector<Token> tokens = tokenize(source);

    std::cout << std::endl << std::endl;

    // Printing tokens to command line    
    {
        int i = 0;
        while (i < tokens.size()) {
            if (tokens[i].type == TokenType::var_name) {
                std::cout << "var_name: " << tokens[i].value.value() << std::endl;
                i++;
                continue;
            }
            std::cout << returnStringFromType(tokens[i].type) << std::endl;
            i++;
        }
    }

    return 0;
}