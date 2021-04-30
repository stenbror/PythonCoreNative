
#include <ast/DecoratorStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DecoratorStatementNode::DecoratorStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mOp4 = op4;
    mLeft = left;
    mRight = right;
}
