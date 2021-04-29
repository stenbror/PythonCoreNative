
#include <ast/AssertStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AssertStatementNode::AssertStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
}
