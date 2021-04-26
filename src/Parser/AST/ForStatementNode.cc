
#include <ast/ForStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ForStatementNode::ForStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> next,
                            std::shared_ptr<StatementNode> extra
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mOp3 = op3;
    mOp4 = op4;
    mNext = next;
    mExtra = extra;
}
