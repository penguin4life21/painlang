#pragma once

#include "../syntaxtree.hpp"

std::string convertNodeTypeToString(NodeType type) {
    NodeType mapTypes[11] = {
        NodeType::root,
        NodeType::exit,
        NodeType::assign,
        NodeType::integer_literal,
        NodeType::var_name,
        NodeType::operation_plus,
        NodeType::operation_minus,
        NodeType::operation_multi,
        NodeType::operation_divide,
        NodeType::operation_modulus,
        NodeType::operation_pow
    };
    
    std::string mapStrings[11] = {
        "root",
        "exit",
        "assign",
        "integer_literal",
        "var_name",
        "operation_plus",
        "operation_minus",
        "operation_multi",
        "operation_divide",
        "operation_modulus",
        "operation_pow"
    };

    int i = 0;
    while (i < 10) {
        if (type == mapTypes[i]) {
            return(mapStrings[i]);
        }
        i++;
    }
    return("");
}

char INDENT_CHAR = '-';

void printTree(const Node& node, int depth = 0) {
    for (int i = 0; i < depth; ++i) {
        std::cout << INDENT_CHAR;
    }

    std::cout << convertNodeTypeToString(node.type);

    if (node.value) {
        std::cout << " (" << *node.value << ")";
    }

    std::cout << "\n";

    for (const auto& child : node.children) {
        printTree(child, depth + 1);
    }

}