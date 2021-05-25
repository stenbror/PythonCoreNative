
#include <ast/TFPDefStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TFPDefStatementNode::TFPDefStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<Token> TFPDefStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> TFPDefStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<ExpressionNode> TFPDefStatementNode::GetRight()
{
    return mRight;
}
