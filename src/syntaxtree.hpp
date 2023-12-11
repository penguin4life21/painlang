#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <stack>

#include "token.hpp"

#include "utils/tokentypetostring.hpp"

enum class NodeType
{
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
    operation_pow
};

struct Node
{
    std::vector<Node> children;
    NodeType type;
    std::optional<std::string> value;
};

int getOperatorPrecedence(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/" || op == "%")
        return 2;
    if (op == "^")
        return 3;
    return 0; // Assuming 0 precedence for non-operators
}

//! SEGFAULT in here
Node shuntingYardAlgorithm(const std::vector<Token> &equation)
{
    std::stack<Token> operatorStack;
    std::vector<Token> outputQueue;

    std::function<void()> processOperator = [&]()
    {
        while (!operatorStack.empty() &&
               getOperatorPrecedence(operatorStack.top().value.value_or("")) >=
                   getOperatorPrecedence(outputQueue.back().value.value_or("")))
        {
            outputQueue.push_back(operatorStack.top());
            operatorStack.pop();
        }
        operatorStack.push(outputQueue.back());
        if (!outputQueue.empty()) {
            outputQueue.pop_back(); 
        } else {
            //! Case handling
            std::cout << "In processOperator: Could not pop_back on outputQueue due to it being empty" << std::endl;
        }
    };

    std::function<void()> processCloseParen = [&]()
    {
        while (!operatorStack.empty() && operatorStack.top().type != TokenType::begin_paren)
        {
            outputQueue.push_back(operatorStack.top());
            operatorStack.pop();
        }
        operatorStack.pop(); 
    };

    std::stack<Node> syntaxTreeStack;

    std::function<void()> buildSyntaxTree = [&]()
    {
        Node operatorNode;
        operatorNode.type = NodeType::operation_plus; 
        operatorNode.value = outputQueue.back().value;

        if (!outputQueue.empty())
        {
            outputQueue.pop_back();
        }
        else
        {
            //! Case handling
            std::cout << "In buildSyntaxTree: Could not pop_back on outputQueue due to it being empty" << std::endl;
        }

        operatorNode.children.push_back({}); 
        operatorNode.children.push_back({}); 

        std::swap(operatorNode.children[0], syntaxTreeStack.top());
        syntaxTreeStack.pop();
        std::swap(operatorNode.children[1], syntaxTreeStack.top());
        syntaxTreeStack.pop();

        syntaxTreeStack.push(operatorNode);
    };

    std::function<void(const Token &)> processToken = [&](const Token &token)
    {
        if (token.type == TokenType::integer_literal ||
            token.type == TokenType::var_name)
        {
            outputQueue.push_back(token);
        }
        else if (token.type == TokenType::plus ||
                 token.type == TokenType::minus ||
                 token.type == TokenType::star ||
                 token.type == TokenType::forward_slash ||
                 token.type == TokenType::modulus ||
                 token.type == TokenType::pow)
        {
            processOperator();
            operatorStack.push(token);
        }
        else if (token.type == TokenType::begin_paren)
        {
            operatorStack.push(token);
        }
        else if (token.type == TokenType::end_paren)
        {
            processCloseParen();
        }
    };

    std::function<void()> processOutputQueue = [&]()
    {
        while (!outputQueue.empty())
        {
            if (outputQueue.back().type == TokenType::plus ||
                outputQueue.back().type == TokenType::minus ||
                outputQueue.back().type == TokenType::star ||
                outputQueue.back().type == TokenType::forward_slash ||
                outputQueue.back().type == TokenType::modulus ||
                outputQueue.back().type == TokenType::pow)
            {
                buildSyntaxTree();
            }
            else
            {
                syntaxTreeStack.push({.type = NodeType::integer_literal,
                                      .value = outputQueue.back().value});
            }
            if (!outputQueue.empty()) {
                outputQueue.pop_back();
            } else {
                //! Case handling
                std::cout << "In processOutputQueue: Could not pop_back on outputQueue due to it being empty" << std::endl;
            }
        }
    };

    std::function<void()> processOperatorStack = [&]()
    {
        while (!operatorStack.empty())
        {
            outputQueue.push_back(operatorStack.top());
            operatorStack.pop();
        }
    };

    // Main loop
    std::vector<Token>::const_reverse_iterator it = equation.rbegin(); 
    while (it != equation.rend())
    {
        processToken(*it);
        it++;
    }

    return Node();

    processOutputQueue();
    processOperatorStack();


    if (!syntaxTreeStack.empty())
    {
        return syntaxTreeStack.top();
    }
    else
    {
        std::cerr << "Error building syntax tree!" << std::endl;
        return Node(); 
    }
}

#include "utils/printAST.hpp"

Node convertToAST(std::vector<Token> tokens)
{
    std::vector<Token> tokensClone = tokens;

    Node root;
    root.type = NodeType::root;

    while (!tokens.empty())
    {
        if (tokens[0].type == TokenType::def)
        {
            std::vector<Token> currentLine;
            Node currentNode;

            while (tokens[0].type != TokenType::end_line)
            {
                currentLine.push_back(tokens[0]);
                tokens.erase(tokens.begin());
            }

            std::cout << currentLine.size() << "\n";

            tokens.erase(tokens.begin());

            if (currentLine.size() == 3)
            {
                currentNode.type = NodeType::assign;

                Node varNameNode;
                varNameNode.type = NodeType::var_name;
                varNameNode.value = currentLine[2].value;

                currentNode.children.push_back(varNameNode);

                root.children.push_back(currentNode);
            }
            else if (currentLine.size() == 5)
            {
                currentNode.type = NodeType::assign;

                Node varNameNode;
                varNameNode.type = NodeType::var_name;
                varNameNode.value = currentLine[2].value;

                currentNode.children.push_back(varNameNode);

                if (currentLine[4].type == TokenType::integer_literal)
                {
                    Node intValueNode;
                    intValueNode.type = NodeType::integer_literal;
                    intValueNode.value = currentLine[4].value;

                    currentNode.children.push_back(intValueNode);

                    root.children.push_back(currentNode);
                }
            }
            else if (currentLine.size() > 5)
            {
                currentNode.type = NodeType::assign;

                Node varNameNode;
                varNameNode.type = NodeType::var_name;
                varNameNode.value = currentLine[2].value;

                currentNode.children.push_back(varNameNode);

                currentLine.erase(currentLine.begin(), currentLine.begin() + 4);

                std::cout << "[";
                int lineCountPrint = 0;
                while (lineCountPrint < currentLine.size())
                {
                    std::cout << returnStringFromType(currentLine[lineCountPrint].type) << ", ";
                    lineCountPrint++;
                }
                std::cout << returnStringFromType(currentLine[lineCountPrint].type) << "]\n";

                // ! TODO :::: DO ASAP
                // Equation Parsing
                Node equationNode = shuntingYardAlgorithm(currentLine);
                printTree(equationNode);
                std::cout << "\n\n";
            }
        }
        else
        {
            tokens.erase(tokens.begin());
        }
    }

    printTree(root);

    return root;
}
