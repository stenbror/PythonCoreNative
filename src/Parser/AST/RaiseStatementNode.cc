
#include <ast/RaiseStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

RaiseStatementNode::RaiseStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<Token> RaiseStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> RaiseStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> RaiseStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> RaiseStatementNode::GetRight()
{
    return mRight;
}
