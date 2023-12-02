#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "token.hpp"
#include "syntaxanalyser.hpp"
#include "syntaxtree.hpp"

#include "interpret.hpp"

#include "utils/tokentypetostring.hpp"

void printTokens(std::vector<Token> tokenVector) {
    int i = 0;
    while (i < tokenVector.size()) {
        if (tokenVector[i].type == TokenType::end_line) {
            std::cout << "end_line" << std::endl << std::endl;
            i++;
            continue;
        }
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


// argv[1] = Run Mode ("-i" -> Interpret, "-c" -> Compile)
// argv[2] = Input File
int main(int argc, char* argv[]) {
    std::ifstream file(argv[2]);

    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string source;
    source = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    file.close();

    if (source.substr(0, 12) != "#--[include]") {
        std::cerr << "Invalid code header" << std::endl;
    }
    source.erase(0, 12);
    
    int endHeaderpos;
    endHeaderpos = source.find("#--\n", 0);
    if (endHeaderpos == -1) {
        std::cerr << "No end of header found" << std::endl;
    }
    source.erase(0,endHeaderpos + 4);

    std::vector<Token> tokens = tokenize(source);

    std::vector<Token> analysedTokens = parse(tokens);

    printTokens(analysedTokens);

    Node ast = convertToAST(analysedTokens);

    return 0;

    std::cout << "\n\n";

    std::string argv_1 = argv[1];
    if (argv_1 == "-i") {
        interpret(analysedTokens);
    }

    return 0;
}