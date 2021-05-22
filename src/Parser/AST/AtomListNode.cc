
#include <ast/AtomListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomListNode::AtomListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;
}
std::shared_ptr<Token> AtomListNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> AtomListNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> AtomListNode::GetOperator2()
{
    return mOp2;
}
