#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

const std::string specialEscapeChars = "()+-";

enum class TokenType {
    exit,
    integer,
    integer_literal,
    begin_paren,
    end_paren,
    begin_curly,
    end_curly,
    def,
    assign,
    if_,
    func,
    eq,
    plus,
    minus,
    star,
    forward_slash,
    modulus,
    whitespace,
    end_line,
    var_name
};

#include "utils/tokentypetostring.hpp"

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

bool isSpecialChar(char character) {
    // if (specialEscapeChars.find(character) != std::string::npos) {
    //     std::cout << "1" << std::endl;
    // } else {
    //     std::cout << "0" << std::endl;
    // }
    return(specialEscapeChars.find(character) != std::string::npos);
}

inline std::vector<Token> tokenize(std::string code) {
    std::vector<Token> tokens;

    std::string buffer;

    int i = 0;
    while (i < code.length()) {
        if (code[i] == ';') {
            tokens.push_back({.type = TokenType::end_line});
            i++;
            continue;
        }
        if (std::isalpha(code[i])) {
            buffer += code[i];
            
            while(!(std::isspace(code[i + 1]) || isSpecialChar(code[i + 1]) == 1)) {
                buffer += code[i + 1];
                i++;
            }
            if (code[i + 1] == '(') {
            
                i++;
            }
            if (code[i+1] == ')') {
                i++;
                continue;
            }
        }
        if (buffer == "def") {
            tokens.push_back({.type = TokenType::def});
            buffer.clear();
        }
        if (buffer == "int") {
            tokens.push_back({.type = TokenType::integer});
            buffer.clear();
        }
        if (buffer == "exit") {
            tokens.push_back({.type = TokenType::exit});
            buffer.clear();
        }
        if (buffer != "") {    
            tokens.push_back({.type = TokenType::var_name, .value = buffer});
            buffer.clear();  
        }
        if (code[i] == '(') {
            tokens.push_back({.type = TokenType::begin_paren});
        }
        if (code[i] == ')') {
            tokens.push_back({.type = TokenType::end_paren});
        }
        if (code[i] == '=') {
            tokens.push_back({.type = TokenType::assign});
        }

        if (std::isdigit(code[i])) {
            // buffer += 
        }

        i++;
    }

    return tokens;
}
