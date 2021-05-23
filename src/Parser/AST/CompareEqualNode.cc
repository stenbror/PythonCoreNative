
#include <ast/CompareEqualNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompareEqualNode::CompareEqualNode(  
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

std::shared_ptr<ExpressionNode>  CompareEqualNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> CompareEqualNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> CompareEqualNode::GetRight()
{
    return mRight;
}
