
#include <ast/SyncCompForNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SyncCompForNode::SyncCompForNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<ExpressionNode> next
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mLeft = left;
    mRight = right;
    mNext = next;
}

std::shared_ptr<ExpressionNode> SyncCompForNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> SyncCompForNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> SyncCompForNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> SyncCompForNode::GetRight()
{
    return mRight;
}

std::shared_ptr<ExpressionNode> SyncCompForNode::GetNext()
{
    return mNext;
}
