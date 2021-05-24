
#include <ast/MulNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

MulNode::MulNode(  
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

std::shared_ptr<ExpressionNode> MulNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> MulNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> MulNode::GetRight()
{
    return mRight;
}
