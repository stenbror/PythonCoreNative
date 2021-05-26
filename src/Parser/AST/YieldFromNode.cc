
#include <ast/YieldFromNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

YieldFromNode::YieldFromNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<Token> YieldFromNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> YieldFromNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> YieldFromNode::GetRight()
{
    return mRight;
}
