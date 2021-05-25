
#include <ast/ShiftRightNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ShiftRightNode::ShiftRightNode(  
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

std::shared_ptr<ExpressionNode> ShiftRightNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ShiftRightNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> ShiftRightNode::GetRight()
{
    return mRight;
}
