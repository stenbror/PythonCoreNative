
#include <ast/SubscriptNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
