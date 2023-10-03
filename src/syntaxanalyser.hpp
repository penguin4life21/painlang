#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "token.hpp"

struct Var {
    // For some strange reason std::vector::push_back will throw and error if both fields are required and can't be bothered to look into it
    std::optional<std::string> name;
    TokenType type;
};

inline std::vector<Token> parse(std::vector<Token> tokens) {
    std::vector<Token> returnTokens;
    std::vector<Token> currentLine;
    std::vector<Var> definedVars;

    int i = 1;

    while (!tokens.empty()) {
        while (tokens[0].type != TokenType::end_line) {
            currentLine.push_back(tokens[0]);
            tokens.erase(tokens.begin());
        }
        tokens.erase(tokens.begin());

        if (currentLine[0].type == TokenType::def) {
            // Declaration
            if (currentLine.size() == 3) {
                
            } else
            // Assignment with value
            if (currentLine.size() == 5) {

            } else
            // Assignment with Expression
            if (currentLine.size() > 5) {

            }
        } else
        if (currentLine[0].type == TokenType::exit) {

        } 

        // {
        //     int k = 0;
        //     while (k < currentLine.size()) {
        //         if (currentLine[k].type == TokenType::var_name) {
        //             std::cout << "var_name: " << currentLine[k].value.value() << std::endl;
        //             k++;
        //             continue;
        //         }
        //         if (currentLine[k].type == TokenType::integer_literal) {
        //             std::cout << "integer_literal: " << currentLine[k].value.value() << std::endl;
        //             k++;
        //             continue;
        //         }
        //         std::cout << returnStringFromType(currentLine[k].type) << std::endl;
        //         k++;
        //     }
        // } 


        int l = 0;
        while (l < currentLine.size()) {
            returnTokens.push_back(currentLine[l]);
            l++;
        }
        returnTokens.push_back({.type = TokenType::end_line});

        currentLine.clear();

        i++;
    }

    return(returnTokens);
}