
#include <ast/UnaryPlusNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

UnaryPlusNode::UnaryPlusNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> UnaryPlusNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> UnaryPlusNode::GetRight()
{
    return mRight;
}
