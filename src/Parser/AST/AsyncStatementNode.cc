
#include <ast/AsyncStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AsyncStatementNode::AsyncStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> AsyncStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<StatementNode> AsyncStatementNode::GetRight()
{
    return mRight;
}
