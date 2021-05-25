
#include <ast/TestNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TestNode::TestNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> next
                        ) : ExpressionNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
    mNext = next;
}

std::shared_ptr<ExpressionNode> TestNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> TestNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> TestNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> TestNode::GetRight()
{
    return mRight;
}

std::shared_ptr<ExpressionNode> TestNode::GetNext()
{
    return mNext;
}
