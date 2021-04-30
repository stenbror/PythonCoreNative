
#include <ast/ClassStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ClassStatementNode::ClassStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<Token> op5,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mLeft = left;
    mOp4 = op4;
    mOp5 = op5;
    mRight = right;
}
