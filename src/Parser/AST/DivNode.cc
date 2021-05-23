
#include <ast/DivNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DivNode::DivNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mRight = right;
}

std::shared_ptr<ExpressionNode> DivNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> DivNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> DivNode::GetRight()
{
    return mRight;
}
