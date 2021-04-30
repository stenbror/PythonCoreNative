
#include <ast/ImportStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ImportStatementNode::ImportStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mRight = right;
}
