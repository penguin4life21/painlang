#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

const std::string specialEscapeChars = "()+-*/%;";

enum class TokenType {
    exit,
    integer,
    integer_literal,
    string,
    string_literal,
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
        }
        if (buffer == "def") {
            tokens.push_back({.type = TokenType::def});
            buffer.clear();
        } else
        if (buffer == "int") {
            tokens.push_back({.type = TokenType::integer});
            buffer.clear();
        } else
        if (buffer == "exit") {
            tokens.push_back({.type = TokenType::exit});
            buffer.clear();
        } else
        if (buffer != "") {    
            tokens.push_back({.type = TokenType::var_name, .value = buffer});
            buffer.clear(); 
        } else
        if (code[i] == '(') {
            tokens.push_back({.type = TokenType::begin_paren});
        } else
        if (code[i] == ')') {
            tokens.push_back({.type = TokenType::end_paren});
        } else
        if (code[i] == '=' && code[i + 1] != '=' && code[i-1] != '=') {
            tokens.push_back({.type = TokenType::assign});
        } else
        if (code[i] == '+') {
            tokens.push_back({.type = TokenType::plus});
        } else 
        if (code[i] == '-') {
            tokens.push_back({.type = TokenType::minus});
        } else
        if (code[i] == '*') {
            tokens.push_back({.type = TokenType::star});
        } else
        if (code[i] == '/') {
            tokens.push_back({.type = TokenType::forward_slash});
        } else
        if (code[i] == '%') {
            tokens.push_back({.type = TokenType::modulus});
        } else

        if (std::isdigit(code[i])) {
            buffer += code[i];
            if (isSpecialChar(code[i + 1]) == 1) {
                tokens.push_back({.type = TokenType::integer_literal, .value = buffer});
            } else {
                while (!(std::isspace(code[i + 1]) || isSpecialChar(code[i + 1]) == 1)) {
                    if (std::isdigit(code[i + 1])) {
                        buffer += code[i + 1];
                        i++;
                    } else {
                        tokens.push_back({.type = TokenType::integer_literal, .value = buffer});
                        break;
                    }
                }
                tokens.push_back({.type = TokenType::integer_literal, .value = buffer});
            }
            buffer.clear();
        }

        i++;
    }

    return tokens;
}
