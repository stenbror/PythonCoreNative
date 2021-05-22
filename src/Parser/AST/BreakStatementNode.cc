
#include <ast/BreakStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

BreakStatementNode::BreakStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<Token> BreakStatementNode::GetOperator()
{
    return mOp1;
}
