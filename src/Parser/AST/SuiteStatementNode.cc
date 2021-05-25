
#include <ast/SuiteStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SuiteStatementNode::SuiteStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<Token> op3
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mNodes = nodes;
    mNewlines = newlines;
    mOp3 = op3;
}

std::shared_ptr<Token> SuiteStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> SuiteStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> SuiteStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> SuiteStatementNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> SuiteStatementNode::GetNewlines()
{
    return mNewlines;
}
