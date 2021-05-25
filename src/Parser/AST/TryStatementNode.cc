
#include <ast/TryStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TryStatementNode::TryStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> exceptNodes,
                            std::shared_ptr<StatementNode> elseNode,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mOp3 = op3;
    mOp4 = op4;
    mExceptNodes = exceptNodes;
    mElseNode = elseNode;
}

std::shared_ptr<Token> TryStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> TryStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> TryStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> TryStatementNode::GetExceptNodes()
{
    return mExceptNodes;
}

std::shared_ptr<StatementNode> TryStatementNode::GetElseNode()
{
    return mElseNode;
}

std::shared_ptr<Token> TryStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<Token> TryStatementNode::GetOperator4()
{
    return mOp4;
}

std::shared_ptr<StatementNode> TryStatementNode::GetRight()
{
    return mRight;
}
