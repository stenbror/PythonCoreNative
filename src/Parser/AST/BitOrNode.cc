
#include <ast/BitOrNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

BitOrNode::BitOrNode(  
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

std::shared_ptr<ExpressionNode> BitOrNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> BitOrNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> BitOrNode::GetRight()
{
    return mRight;
}
