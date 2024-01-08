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

void handleVariable(Line line, std::vector<InterpretVar> *vars) {
    
}

void interpret(std::vector<Token> tokens) {
    
}