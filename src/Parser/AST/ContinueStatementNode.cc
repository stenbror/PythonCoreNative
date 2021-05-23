
#include <ast/ContinueStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ContinueStatementNode::ContinueStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<Token> ContinueStatementNode::GetOperator()
{
    return mOp1;
}
