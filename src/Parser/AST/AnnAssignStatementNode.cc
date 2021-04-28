
#include <ast/AnnAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AnnAssignStatementNode::AnnAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Node> next
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
    mNext = next;
}
