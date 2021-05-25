
#include <ast/ShiftRightAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ShiftRightAssignStatementNode::ShiftRightAssignStatementNode(  
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

std::shared_ptr<Node> ShiftRightAssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ShiftRightAssignStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> ShiftRightAssignStatementNode::GetyRight()
{
    return mRight;
}
