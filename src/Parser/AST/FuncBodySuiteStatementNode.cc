
#include <ast/FuncBodySuiteStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

FuncBodySuiteStatementNode::FuncBodySuiteStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<Token> op5
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mOp4 = op4;
    mNodes = nodes;
    mNewlines = newlines;
    mOp5 = op5;
}

std::shared_ptr<Token> FuncBodySuiteStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> FuncBodySuiteStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> FuncBodySuiteStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<Token> FuncBodySuiteStatementNode::GetOperator4()
{
    return mOp4;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> FuncBodySuiteStatementNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> FuncBodySuiteStatementNode::GetNewlines()
{
    return mNewlines;
}

std::shared_ptr<Token> FuncBodySuiteStatementNode::GetOperatror5()
{
    return mOp5;
}
