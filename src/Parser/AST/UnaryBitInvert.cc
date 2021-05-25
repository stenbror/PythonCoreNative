
#include <ast/UnaryBitInvertNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

UnaryBitInvertNode::UnaryBitInvertNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> UnaryBitInvertNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> UnaryBitInvertNode::GetRight()
{
    return mRight;
}
