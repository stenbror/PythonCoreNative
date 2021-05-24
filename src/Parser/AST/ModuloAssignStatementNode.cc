
#include <ast/ModuloAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ModuloAssignStatementNode::ModuloAssignStatementNode(  
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

std::shared_ptr<Node> ModuloAssignStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ModuloAssignStatementNode::GetOerator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> ModuloAssignStatementNode::GetRight()
{
    return mRight;
}
