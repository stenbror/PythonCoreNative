
#include <ast/CallNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CallNode::CallNode(  
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

std::shared_ptr<Token> CallNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> CallNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> CallNode::GetOperator2()
{
    return mOp2;
}
