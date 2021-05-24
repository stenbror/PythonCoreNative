
#include <ast/ImportFromStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ImportFromStatementNode::ImportFromStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op4
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mOp4 = op4;
    mLeft = left;
    mRight = right;
    mDots = dots;
}

std::shared_ptr<Token> ImportFromStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> ImportFromStatementNode::GetDots()
{
    return mDots;
}

std::shared_ptr<StatementNode> ImportFromStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ImportFromStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> ImportFromStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<StatementNode> ImportFromStatementNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> ImportFromStatementNode::GetOperator4()
{
    return mOp4;
}
