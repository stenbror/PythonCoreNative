
#include <ast/ReturnStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ReturnStatementNode::ReturnStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> ReturnStatementNode::GetOperator()
{
    return mOp1;
} 

std::shared_ptr<StatementNode> ReturnStatementNode::GetRight()
{
    return mRight;
}
