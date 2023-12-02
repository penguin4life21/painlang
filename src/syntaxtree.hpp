#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <optional>

#include "token.hpp"

#include "utils/tokentypetostring.hpp"

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
    std::vector<Node> children;
    std::optional<NodeType> type;
    std::optional<std::string> value;
};

Node convertToAST(std::vector<Token> tokens) {
    std::vector<Token> tokensClone = tokens;

    Node root;
    root.type = NodeType::root;
    
    while (!tokens.empty()) {
        if (tokens[0].type == TokenType::def) {
            std::vector<Token> currentLine;
            Node currentNode;

            while (tokens[0].type != TokenType::end_line) {
                currentLine.push_back(tokens[0]);
                tokens.erase(tokens.begin());
            }
            
            std::cout << currentLine.size() << "\n";

            tokens.erase(tokens.begin());

            if (currentLine.size() == 3) {
                    currentNode.type = NodeType::assign;

                    Node varNameNode;
                    varNameNode.type = NodeType::var_name;
                    varNameNode.value = currentLine[2].value;

                    currentNode.children.push_back(varNameNode);
            } else if (currentLine.size() == 5) {
                    currentNode.type = NodeType::assign;

                    Node varNameNode;
                    varNameNode.type = NodeType::var_name;
                    varNameNode.value = currentLine[2].value;
                    
                    currentNode.children.push_back(varNameNode);

                    if (currentLine[4].type == TokenType::integer_literal) {
                        Node intValueNode;
                        intValueNode.type = NodeType::integer_literal;
                        intValueNode.value = currentLine[4].value;

                        currentNode.children.push_back(intValueNode);
                    }
            } else if (currentLine.size() > 5) {
                currentNode.type = NodeType::assign;

                Node varNameNode;
                varNameNode.type = NodeType::var_name;
                varNameNode.value = currentLine[2].value;

                currentNode.children.push_back(varNameNode);

                currentLine.erase(currentLine.begin(), currentLine.begin() + 4);

                std::cout << "[";
                while (currentLine.size() > 1) {
                    std::cout << returnStringFromType(currentLine[0].type) << ", ";
                    currentLine.erase(currentLine.begin());
                }
                std::cout << returnStringFromType(currentLine[0].type) << "]\n";
                

                


                Node equationNode;

                
                
            }

        } else {
            tokens.erase(tokens.begin());
        }
    }

    return root;
}
