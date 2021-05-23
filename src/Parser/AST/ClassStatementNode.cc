
#include <ast/ClassStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

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

std::shared_ptr<Token> ClassStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> ClassStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> ClassStatementNode::GetOperators3()
{
    return mOp3;
}

std::shared_ptr<ExpressionNode> ClassStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ClassStatementNode::GetOperator4()
{
    return mOp4;
}

std::shared_ptr<Token> ClassStatementNode::GetOperator5()
{
    return mOp5;
}

std::shared_ptr<StatementNode> ClassStatementNode::GetRight()
{
    return mRight;
}
