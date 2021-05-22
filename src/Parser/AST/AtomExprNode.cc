
#include <ast/AtomExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomExprNode::AtomExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mRight = right;
}

std::shared_ptr<Token> AtomExprNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> AtomExprNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> AtomExprNode::GetRight()
{
    return mRight;
}
