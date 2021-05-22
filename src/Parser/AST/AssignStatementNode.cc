
#include <ast/AssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AssignStatementNode::AssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> ops,
                            std::shared_ptr<std::vector<std::shared_ptr<Node>>> rightNodes,
                            std::shared_ptr<Token> op2
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOps = ops;
    mOp2 = op2;
    mRightNodes = rightNodes;
}

std::shared_ptr<Node> AssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> AssignStatementNode::GetOperators()
{
    return mOps;
}

std::shared_ptr<std::vector<std::shared_ptr<Node>>> AssignStatementNode::GetRightNodes()
{
    return mRightNodes;
}

std::shared_ptr<Token> AssignStatementNode::GetOperator2()
{
    return mOp2;
}
