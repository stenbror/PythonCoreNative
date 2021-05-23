
#include <ast/ComplexNumberNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ComplexNumberNode::ComplexNumberNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NumberToken> real,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NumberToken> imaginary
                        ) : StatementNode(start, end)
{
    
    mRealSign = op1;
    mReal = real;
    mImaginarySign = op2;
    mImaginary = imaginary;

}

std::shared_ptr<Token> ComplexNumberNode::GetRealSign()
{
    return mRealSign;
}

std::shared_ptr<NumberToken> ComplexNumberNode::GetReal()
{
    return mReal;
}

std::shared_ptr<Token> ComplexNumberNode::GetImaginarySign()
{
    return mImaginarySign;
}

std::shared_ptr<NumberToken> ComplexNumberNode::GetImaginary()
{
    return mImaginary;
}
