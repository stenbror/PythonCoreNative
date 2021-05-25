
#include <ast/SubscriptNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SubscriptNode::SubscriptNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> next
                        ) : ExpressionNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;
    mNext = next;
}

 std::shared_ptr<ExpressionNode> SubscriptNode::GetLeft()
 {
     return mLeft;
 }

std::shared_ptr<Token> SubscriptNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> SubscriptNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> SubscriptNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> SubscriptNode::GetNext()
{
    return mNext;
}
