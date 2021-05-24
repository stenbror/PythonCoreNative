
#include <ast/FloorDivAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

FloorDivAssignStatementNode::FloorDivAssignStatementNode(  
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

std::shared_ptr<Node> FloorDivAssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> FloorDivAssignStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> FloorDivAssignStatementNode::GetRight()
{
    return mRight;
}
