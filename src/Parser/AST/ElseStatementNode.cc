
#include <ast/ElseStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ElseStatementNode::ElseStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<Token> ElseStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> ElseStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> ElseStatementNode::GetRight()
{
    return mRight;
}
