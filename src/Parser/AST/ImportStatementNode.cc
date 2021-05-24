
#include <ast/ImportStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ImportStatementNode::ImportStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}

std::shared_ptr<Token> ImportStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<StatementNode> ImportStatementNode::GetRight()
{
    return mRight;
}
