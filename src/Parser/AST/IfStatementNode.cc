
#include <ast/IfStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

IfStatementNode::IfStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mNodes = nodes;
    mNext = next;
}

std::shared_ptr<Token> IfStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> IfStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> IfStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> IfStatementNode::GetRight()
{
    return mRight;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> IfStatementNode::GetElifNodes()
{
    return mNodes;
}

std::shared_ptr<StatementNode> IfStatementNode::GetGetElseNode()
{
    return mNext;
}
