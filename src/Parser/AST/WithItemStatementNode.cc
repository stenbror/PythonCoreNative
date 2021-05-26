
#include <ast/WithItemStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

WithItemStatementNode::WithItemStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<ExpressionNode> WithItemStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> WithItemStatementNode::GetOperator()
{
    return mOp1;
}
std::shared_ptr<ExpressionNode> WithItemStatementNode::GetRight()
{
    return mRight;
}
