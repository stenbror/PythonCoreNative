
#include <ast/ExceptNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ExceptNode::ExceptNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mRight = right;
}

std::shared_ptr<StatementNode> ExceptNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ExceptNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<StatementNode> ExceptNode::GetRight()
{
    return mRight;
}
