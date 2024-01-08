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
    operation_pow,
    begin_paren,
    end_paren
};

struct Node
{
    std::vector<Node> children;
    NodeType type;
    std::optional<std::string> value;
};

int getOperatorPrecedence(const TokenType &op)
{
    if (op == TokenType::plus || op == TokenType::minus)
    {
        return 1;
    }
    if (op == TokenType::star || op == TokenType::forward_slash || op == TokenType::modulus)
    {
        return 2;
    }
    if (op == TokenType::pow)
    {
        return 3;
    }
    return 0;
}

int getOperatorPrecedence(NodeType op)
{
    if (op == NodeType::operation_plus || op == NodeType::operation_minus)
    {
        return 1;
    }
    if (op == NodeType::operation_multi || op == NodeType::operation_divide || op == NodeType::operation_modulus)
    {
        return 2;
    }
    if (op == NodeType::operation_pow)
    {
        return 3;
    }
    return 0;
}

#include "utils/printAST.hpp"

bool isOperator(TokenType type)
{
    return type == TokenType::plus || type == TokenType::minus ||
           type == TokenType::star || type == TokenType::forward_slash ||
           type == TokenType::modulus || type == TokenType::pow;
}

NodeType tokenTypeToNodeType(TokenType type)
{
    switch (type) {
        case TokenType::plus:
            return NodeType::operation_plus;
        case TokenType::minus:
            return NodeType::operation_minus;
        case TokenType::star:
            return NodeType::operation_multi;
        case TokenType::forward_slash:
            return NodeType::operation_divide;
        case TokenType::modulus:
            return NodeType::operation_modulus;
        case TokenType::pow:
            return NodeType::operation_pow;
        default:
            throw std::invalid_argument("Invalid token type for conversion");
    }
}

Node shuntingYardAlgorithm(std::vector<Token> &tokens)
{
    std::stack<Token> operatorStack;
    std::stack<Node> operandStack;

    while (!tokens.empty())
    {
        Token token = tokens[0];
        tokens.erase(tokens.begin());

        if (token.type == TokenType::integer_literal)
        {
            Node operandNode;
            operandNode.type = NodeType::integer_literal;
            operandNode.value = token.value;
            operandStack.push(operandNode);
        }
        else if (token.type == TokenType::var_name)
        {
            Node operandNode;
            operandNode.type = NodeType::var_name;
            operandNode.value = token.value;
            operandStack.push(operandNode);
        }
        else if (isOperator(token.type))
        {
            while (!operatorStack.empty() &&
                   getOperatorPrecedence(operatorStack.top().type) >= getOperatorPrecedence(token.type))
            {
                Node rightOperand = operandStack.top();
                operandStack.pop();

                Node leftOperand = operandStack.top();
                operandStack.pop();

                Node operationNode;
                operationNode.type = tokenTypeToNodeType(operatorStack.top().type);
                operationNode.children.push_back(leftOperand);
                operationNode.children.push_back(rightOperand);

                operandStack.push(operationNode);

                operatorStack.pop();
            }

            operatorStack.push(token);
        }
        else if (token.type == TokenType::begin_paren)
        {
            operatorStack.push(token);
        }
        else if (token.type == TokenType::end_paren)
        {
            while (!operatorStack.empty() && operatorStack.top().type != TokenType::begin_paren)
            {
                Node rightOperand = operandStack.top();
                operandStack.pop();

                Node leftOperand = operandStack.top();
                operandStack.pop();

                Node operationNode;
                operationNode.type = tokenTypeToNodeType(operatorStack.top().type);
                operationNode.children.push_back(leftOperand);
                operationNode.children.push_back(rightOperand);

                operandStack.push(operationNode);

                operatorStack.pop();
            }
        
            operatorStack.pop();
        }
    }

    return(Node());

    while (!operatorStack.empty())
    {
        Node rightOperand = operandStack.top();
        operandStack.pop();

        Node leftOperand = operandStack.top();
        operandStack.pop();

        Node operationNode;
        operationNode.type = tokenTypeToNodeType(operatorStack.top().type);
        operationNode.children.push_back(leftOperand);
        operationNode.children.push_back(rightOperand);

        operandStack.push(operationNode);

        operatorStack.pop();
    }

    return operandStack.top();
}

Node convertToAST(std::vector<Token> tokens)
{
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

                Node equationNode = shuntingYardAlgorithm(currentLine);
                printTree(equationNode);
                std::cout << "\n";

                currentNode.children.push_back(equationNode);
                root.children.push_back(currentNode);
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
