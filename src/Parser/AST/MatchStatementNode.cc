
#include <ast/MatchStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

MatchStatementNode::MatchStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> op5
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mOp3 = op3;
    mOp4 = op4;
    mNodes = nodes;
    mOp3 = op5;
}

std::shared_ptr<Token> MatchStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> MatchStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> MatchStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<Token> MatchStatementNode::GetOperator4()
{
    return mOp4;
}

std::shared_ptr<Token> MatchStatementNode::GetOperator5()
{
    return mOp5;
}

std::shared_ptr<AST::StatementNode> MatchStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> MatchStatementNode::GetNodes()
{
    return mNodes;
}
