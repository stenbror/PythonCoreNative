
#include <ast/MulNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

MulNode::MulNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mRight = right;
}
