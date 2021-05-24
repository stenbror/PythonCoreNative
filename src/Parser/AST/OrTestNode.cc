
#include <ast/OrTestNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

OrTestNode::OrTestNode(  
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

std::shared_ptr<ExpressionNode> OrTestNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> OrTestNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> OrTestNode::GetRight()
{
    return mRight;
}
