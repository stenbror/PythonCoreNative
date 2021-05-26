
#include <ast/WhileStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

WhileStatementNode::WhileStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mNext = next;
}

std::shared_ptr<Token> WhileStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> WhileStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> WhileStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> WhileStatementNode::GetRight()
{
    return mRight;
}

std::shared_ptr<StatementNode> WhileStatementNode::GetNext()
{
    return mNext;
}
