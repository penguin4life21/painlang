#pragma once

#include <string>
#include <vector>

enum class Tokens {
    endl,
    exit,
    integer,
    begin_paren,
    end_paren,
    begin_curly,
    end_curly,
    def,
    func,
    eq,
    plus,
    minus,
    star,
    forward_slash,
    modulus,
}

struct Token {
    TokenType type;
    std::optional<std::string> value {};
}

class tokenizer
{
private:
public:
    inline std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::string buffer;


    }
}
