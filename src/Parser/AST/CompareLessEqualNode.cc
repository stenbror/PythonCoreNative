
#include <ast/CompareLessEqualNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompareLessEqualNode::CompareLessEqualNode(  
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

std::shared_ptr<ExpressionNode>  CompareLessEqualNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> CompareLessEqualNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> CompareLessEqualNode::GetRight()
{
    return mRight;
}
