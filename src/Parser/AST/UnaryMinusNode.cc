
#include <ast/UnaryMinusNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

UnaryMinusNode::UnaryMinusNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}
