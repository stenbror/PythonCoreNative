
#include <ast/SubjectExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

SubjectExprNode::SubjectExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mRight = right;
}

std::shared_ptr<ExpressionNode> SubjectExprNode::GetRight()
{
    return mRight;
}
