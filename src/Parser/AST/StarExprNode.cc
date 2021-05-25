
#include <ast/StarExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

StarExprNode::StarExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> StarExprNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> StarExprNode::GetRight()
{
    return mRight;
}
