#include "token.h"
#include <iostream>
#include <stdlib.h>

Token::Token(){}

Token::Token(Type type, int value)
{
    _type = type;
    _value = value;
}

Token::Token(Type type)
{
    _type = type;
}

void Token::printToken()
{
    switch (_type)
    {
    case Type::INTERGER:
        std::cout << "TOKEN(INTERGER, " << _value << " )";
        break;
    case Type::PLUS:
        std::cout << "TOKEN(Plus, +  )";
        break;
    default:
        break;
    }
}

Type Token::getType()
{
    return _type;
}

int Token::getValue()
{
    return _value;
}
