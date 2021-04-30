
#include <ast/AsyncStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AsyncStatementNode::AsyncStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}
