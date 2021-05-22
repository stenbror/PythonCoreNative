
#include <ast/AnnAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AnnAssignStatementNode::AnnAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Node> next
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
    mNext = next;
}

std::shared_ptr<Node> AnnAssignStatementNode::GetLeftNode()
{
    return mLeft;
}

std::shared_ptr<Token> AnnAssignStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> AnnAssignStatementNode::GetRightNode()
{
    return mRight;
}

std::shared_ptr<Token> AnnAssignStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Node> AnnAssignStatementNode::GetNextNode()
{
    return mNext;
}
