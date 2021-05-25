
#include <ast/SignedNumberNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SignedNumberNode::SignedNumberNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> sign,
                            std::shared_ptr<NumberToken> number
                        ) : StatementNode(start, end)
{
    
    mSign = sign;
    mNumber = number;

}

std::shared_ptr<Token> SignedNumberNode::GetSign()
{
    return mSign;
}

std::shared_ptr<NumberToken> SignedNumberNode::GetNumber()
{
    return mNumber;
}
