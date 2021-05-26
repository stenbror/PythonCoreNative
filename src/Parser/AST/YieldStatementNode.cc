
#include <ast/YieldStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

YieldStatementNode::YieldStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mRight = right;
}

std::shared_ptr<ExpressionNode> YieldStatementNode::GetRight()
{
    return mRight;
}
