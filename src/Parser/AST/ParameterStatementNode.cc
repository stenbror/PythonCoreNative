
#include <ast/ParameterStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
