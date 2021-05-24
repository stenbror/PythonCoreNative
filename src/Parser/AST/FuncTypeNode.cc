
#include <ast/FuncTypeNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

FuncTypeNode::FuncTypeNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<TypeNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> right
                        ) : TypeNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mOp3 = op3;
    mRight = right;
}

std::shared_ptr<Token> FuncTypeNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<TypeNode> FuncTypeNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> FuncTypeNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> FuncTypeNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<ExpressionNode> FuncTypeNode::GetRight()
{
    return mRight;
}
