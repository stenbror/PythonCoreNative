
#include <ast/ModuloAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ModuloAssignStatementNode::ModuloAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
}