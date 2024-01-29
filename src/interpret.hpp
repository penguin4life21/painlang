#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "token.hpp"

#include "utils/tokentypetostring.hpp"

struct InterpretVar {
    // For some strange reason std::vector::push_back will throw and error if both fields are required and can't be bothered to look into it
    TokenType type;
    std::optional<std::string> name;

    // Values
    std::optional<int> intVar;
};

struct Line {
    std::vector<Token> tokens;
};

struct LineBoundry {
    int lineStart;
    int lineEnd;
};

void handleVariable(Line line, std::vector<InterpretVar> *vars) {
    
}

void interpret(std::vector<Token> tokens) {
    // Determing index of line boundries and store using LineBoundry struct in a vector
    std::vector<LineBoundry> boundries;

    int tokenIndex = 0;

    int currBegin = 0;
    int currEnd;

    while (tokenIndex < tokens.size()) {
        if (tokens[tokenIndex].type == TokenType::end_line) {
            currEnd = tokenIndex;
            if (tokenIndex + 1 < tokens.size()) {
                currBegin = currEnd += 1;
            }

            boundries.push_back({.lineStart = currBegin, .lineEnd = currEnd});

        }

        tokenIndex += 1;
    }

    std::cout << "Amount of lines -> " << int(boundries.size()) << "\n";

    Line currLine;

    int currLineIndex = 0;


}