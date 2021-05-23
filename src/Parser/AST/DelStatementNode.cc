
#include <ast/DelStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DelStatementNode::DelStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> DelStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> DelStatementNode::GetRight()
{
    return mRight;
}
