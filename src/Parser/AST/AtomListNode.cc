
#include <ast/AtomListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomListNode::AtomListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<NumberToken> op2
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;
}
