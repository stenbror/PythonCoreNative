
#include <ast/ReturnStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ReturnStatementNode::ReturnStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}
