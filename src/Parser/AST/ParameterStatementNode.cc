
#include <ast/ParameterStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ParameterStatementNode::ParameterStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op2
                        ) : StatementNode(start, end)
{
    mRight = right;
    mOp1 = op1;
    mOp2 = op2;
}

std::shared_ptr<Token> ParameterStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> ParameterStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<StatementNode> ParameterStatementNode::GetRight()
{
    return mRight;
}
