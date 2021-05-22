
#include <ast/AssertStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AssertStatementNode::AssertStatementNode(  
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

std::shared_ptr<Token> AssertStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> AssertStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> AssertStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> AssertStatementNode::GetRight()
{
    return mRight;
}
