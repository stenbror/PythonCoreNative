
#include <ast/NamedExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

NamedExprNode::NamedExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<ExpressionNode> NamedExprNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> NamedExprNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> NamedExprNode::GetRight()
{
    return mRight;
}
