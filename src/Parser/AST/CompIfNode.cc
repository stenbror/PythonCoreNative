
#include <ast/CompIfNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompIfNode::CompIfNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<ExpressionNode> next
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
    mNext = next;
}

std::shared_ptr<Token> CompIfNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> CompIfNode::GetRight()
{
    return mRight;
}

std::shared_ptr<ExpressionNode> CompIfNode::GetNext()
{
    return mNext;
}
