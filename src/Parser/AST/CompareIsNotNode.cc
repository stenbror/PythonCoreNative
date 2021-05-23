
#include <ast/CompareIsNotNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompareIsNotNode::CompareIsNotNode(  
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

std::shared_ptr<ExpressionNode>  CompareIsNotNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> CompareIsNotNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> CompareIsNotNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> CompareIsNotNode::GetRight()
{
    return mRight;
}
