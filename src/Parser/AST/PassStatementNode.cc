
#include <ast/PassStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

PassStatementNode::PassStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<Token> PassStatementNode::GetOperator()
{
    return mOp1;
}
