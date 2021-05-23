
#include <ast/CaseStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CaseStatementNode::CaseStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;
    mNext = next;
}

std::shared_ptr<NameToken> CaseStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<StatementNode> CaseStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<StatementNode> CaseStatementNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> CaseStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> CaseStatementNode::GetNext()
{
    return mNext;
}
