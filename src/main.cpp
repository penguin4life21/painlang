#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "token.hpp"
#include "syntaxanalyser.hpp"

#include "utils/tokentypetostring.hpp"

void printTokens(std::vector<Token> tokenVector) {
    int i = 0;
    while (i < tokenVector.size()) {
        if (tokenVector[i].type == TokenType::var_name) {
            std::cout << "var_name: " << tokenVector[i].value.value() << std::endl;
            i++;
            continue;
        }
        if (tokenVector[i].type == TokenType::integer_literal) {
            std::cout << "integer_literal: " << tokenVector[i].value.value() << std::endl;
            i++;
            continue;
        }
        std::cout << returnStringFromType(tokenVector[i].type) << std::endl;
        i++;
    }
}

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
    printTokens(tokens);

    std::vector<Token> parsedTokens = parse(tokens);

    std::cout << std::endl << std::endl;

    printTokens(parsedTokens);

    return 0;
}