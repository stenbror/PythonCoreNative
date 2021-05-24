
#include <ast/PlusAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

PlusAssignStatementNode::PlusAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Node> PlusAssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> PlusAssignStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> PlusAssignStatementNode::GetRight()
{
    return mRight;
}
