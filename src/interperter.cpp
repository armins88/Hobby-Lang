#include "interperter.h"
#include "token.h"
#include <stdlib.h>
#include <iostream>
#include <string>

AST ::AST() {}

AST ::AST(Token token)
{
    _ASTNode->_token = token;
}

AST ::AST(struct ASTNode *node)
{
    _ASTNode = node;
}

AST::AST(std::vector<ASTNode> children)
{
    _children = children;
}

struct ASTNode *AST ::getNode()
{
    return _ASTNode;
}

void AST ::setNode(struct ASTNode *node)
{
    _ASTNode = node;
}

Interperter::Interperter()
{
}

Interperter ::Interperter(Parser parser)
{
    _parser = parser;
}

float Interperter ::visit(ASTNode node)
{
    printf("[INTERPERTER] : visiting ast type: %d \n" , node._type);
    switch (node._type)
    {
    case ASTNodeType::PROGRAM:
    case ASTNodeType::VARDECL:
    case ASTNodeType::Type:
    break;
    case ASTNodeType::BLOCK:
        for(std::vector<ASTNode>::iterator it = node._declarations.begin(); it != node._declarations.begin(); it++)
            visit(*it);
        
        node._type = ASTNodeType::COMPOUND;
        visit(node);
        break;

    case ASTNodeType::COMPOUND:
        std::cout << "[INTERPERTER] Found compound" << std::endl;
        for (ASTNode childNode : node._children)
            visit(childNode);

        return static_cast<float>(NO_OPERATION);
    case ASTNodeType::VAR:
        /** Check if variable exists */
        if (_globalScope.find(node._token.getStringValue()) == _globalScope.end())
        {
            std::cout << "Key not found" << std::endl;
            return static_cast<float>(ERROR_NODE_VISIT);
        }
        return static_cast<float>(_globalScope[node._token.getStringValue()]);
        
    case ASTNodeType::ASSIGN:
        //TODO add some string checking here

        // printf("[INTERPERTER] right node in ASSIGN %d -- %s \n", node._right->_token.getValue(), node._left->_token.getStringValue().c_str());

        _globalScope[node._left->_token.getStringValue()] = visit(*node._right);
        return static_cast<float>(NO_OPERATION);
    case ASTNodeType::BINARY:
        
        switch (node._token.getType())
        {
        case Type::DIV:
            return visit(*node._left) / visit(*node._right);
        case Type::MUL:
            return visit(*node._left) * visit(*node._right);
        case Type::PLUS:
            return visit(*node._left) + visit(*node._right);
        case Type::SUBTRACT:
            return visit(*node._left) - visit(*node._right);
        default:
            return ERROR_NODE_VISIT;
        }
    case ASTNodeType::UNARY:
        switch (node._token.getType())
        {
        case Type::PLUS:
            return visit(*node._right);
        case Type::SUBTRACT:
            return -1 * visit(*node._right);
        default:
            return ERROR_NODE_VISIT;
        }
    case ASTNodeType::VALUE:
        switch (node._token.getType())
        {
        case Type::REAL_CONST:
            return node._token.getFloatValue();
        case Type::INTEGER_CONST:
            return static_cast<float>(node._token.getValue());
        default:
            return static_cast<float>(node._token.getValue());
        }
    case ASTNodeType::NOOP:
        return  static_cast<float>(NO_OPERATION);
    }

    return static_cast<float>(ERROR_NODE_VISIT);
}

void Interperter::printGlobalScope()
{
    for (auto it = _globalScope.begin(); it != _globalScope.end(); ++it)
    {
        std::cout << it->first << " = ";
        printf("%d\n" , it->second);
    }
}

int Interperter ::interpert()
{
    std::cout << "[INTERPERTER] starting to interpert " << std::endl ;
    // ASTNode tree;
    // tree = _parser.parse();

    return visit(_parser.parse().blockNode);
}
