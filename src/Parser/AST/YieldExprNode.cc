
#include <ast/YieldExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

YieldExprNode::YieldExprNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}
