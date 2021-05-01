
#include <ast/YieldFromNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

YieldFromNode::YieldFromNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}