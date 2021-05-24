
#include <ast/MulAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

MulAssignStatementNode::MulAssignStatementNode(  
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

std::shared_ptr<Node> MulAssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> MulAssignStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> MulAssignStatementNode::GetRight()
{
    return mRight;
}
