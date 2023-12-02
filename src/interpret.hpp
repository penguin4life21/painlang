#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "token.hpp"

#include "utils/tokentypetostring.hpp"

struct InterpretVar {
    // For some strange reason std::vector::push_back will throw and error if both fields are required and can't be bothered to look into it
    std::optional<std::string> name;
    TokenType type;

    // Values
    std::optional<int> intVar;
};

struct Line {
    std::vector<Token> tokens;
};

void handleVariable(Line line, std::vector<InterpretVar> *vars) {
    
}

void interpret(std::vector<Token> tokens) {
    // Convert to lines
    std::vector<InterpretVar> variables;

    Line currLine;

    std::vector<Line> lines;

    std::cout << "Start Interpret" << std::endl;

    int i = 0;
    while (i < tokens.size()) {
        currLine.tokens.clear();
        
        int j = 0;
        while (tokens[i + j].type != TokenType::end_line) {
            currLine.tokens.push_back(tokens[i + j]);

            j++;
        }
        
        lines.push_back(currLine);

        i = i + currLine.tokens.size() + 1;
    }

    std::cout << lines.size() << std::endl;
}