
#include <ast/CompareNotInNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompareNotInNode::CompareNotInNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<ExpressionNode>  CompareNotInNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> CompareNotInNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> CompareNotInNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> CompareNotInNode::GetRight()
{
    return mRight;
}
