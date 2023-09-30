#pragma once

#include "../token.hpp"

std::string returnStringFromType(TokenType type) {
    if (type == TokenType::exit) {
        return("exit");
    }
    if (type == TokenType::integer) {
        return("integer");
    }
    if (type == TokenType::integer_literal) {
        return("integer_literal");
    }
    if (type == TokenType::begin_paren) {
        return("begin_paren");
    }
    if (type == TokenType::end_paren) {
        return("end_paren");
    }
    if (type == TokenType::begin_curly) {
        return("begin_curly");
    }
    if (type == TokenType::end_curly) {
        return("end_curly");
    }
    if (type == TokenType::def) {
        return("def");
    }
    if (type == TokenType::assign) {
        return("assign");
    }
    if (type == TokenType::func) {
        return("func");
    }
    if (type == TokenType::eq) {
        return("eq");
    }
    if (type == TokenType::plus) {
        return("plus");
    }
    if (type == TokenType::minus) {
        return("minus");
    }
    if (type == TokenType::star) {
        return("star");
    }
    if (type == TokenType::forward_slash) {
        return("forward_slash");
    }
    if (type == TokenType::modulus) {
        return("modulus");
    }
    if (type == TokenType::whitespace) {
        return("whitespace");
    }
    if (type == TokenType::end_line) {
        return("end_line");
    }
    if (type == TokenType::var_name) {
        return("var_name");
    }
    return("");
}
