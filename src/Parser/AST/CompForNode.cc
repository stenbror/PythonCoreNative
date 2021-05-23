
#include <ast/CompForNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CompForNode::CompForNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> CompForNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> CompForNode::GetRight()
{
    return mRight;
}
