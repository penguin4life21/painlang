#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <optional>

#include "token.hpp"

enum class NodeType {
    root,
    exit,
    assign,
    integer_literal,
    var_name,
    operation_plus,
    operation_minus,
    operation_multi,
    operation_divide,
    operation_modulus,
};

struct Node {
    std::optional<std::vector<Node>> children;
    std::optional<NodeType> type;
    std::optional<std::string> value;
};

Node convertToAST(std::vector<Token> tokens) {
    Node root;
    root.type = NodeType::root;
    
    while (!tokens.empty()) {
        if (tokens[0].type == TokenType::def) {
            std::vector<Token> currentLine;
            Node currNode;
            while (tokens[0].type != TokenType::end_line) {
                currentLine.push_back(tokens[0]);
                tokens.erase(tokens.begin());
            }
            tokens.erase(tokens.begin());

            if (currentLine.size() == 3) {
                if (currentLine[0].type == TokenType::def) {
                    currNode.type = NodeType::assign;
                    Node varNameNode;
                    varNameNode.type = NodeType::var_name;
                    varNameNode.value = currentLine[2].value;
                }
            }

        }
    }

    return root;
}
