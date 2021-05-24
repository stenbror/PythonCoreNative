
#include <ast/LambdaNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

LambdaNode::LambdaNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<ExpressionNode> LambdaNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> LambdaNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> LambdaNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> LambdaNode::GetRight()
{
    return mRight;
}
