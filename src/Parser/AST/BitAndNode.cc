
#include <ast/BitAndNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

BitAndNode::BitAndNode(  
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

std::shared_ptr<ExpressionNode> BitAndNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> BitAndNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> BitAndNode::GetRight()
{
    return mRight;
}
