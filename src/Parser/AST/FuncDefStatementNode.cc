
#include <ast/FuncDefStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

FuncDefStatementNode::FuncDefStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<Token> op5,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mRight = right;
    mNext = next;
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mOp4 = op4;
    mOp5 = op5;
}

std::shared_ptr<Token> FuncDefStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> FuncDefStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> FuncDefStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> FuncDefStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<ExpressionNode> FuncDefStatementNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> FuncDefStatementNode::GetOperator4()
{
    return mOp4;
}

std::shared_ptr<Token> FuncDefStatementNode::GetOperator5()
{
    return mOp5;
}

std::shared_ptr<StatementNode> FuncDefStatementNode::GetNext()
{
    return mNext;
}
