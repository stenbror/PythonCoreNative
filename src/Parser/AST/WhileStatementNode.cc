
#include <ast/WhileStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

WhileStatementNode::WhileStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mNext = next;
}
