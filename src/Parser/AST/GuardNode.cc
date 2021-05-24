
#include <ast/GuardNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

GuardNode::GuardNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;
    
}

std::shared_ptr<Token> GuardNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> GuardNode::GetRight()
{
    return mRight;
}
