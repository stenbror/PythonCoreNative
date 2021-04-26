
#include <ast/SyncCompForNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
