
#include <ast/ExceptClauseNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ExceptClauseNode::ExceptClauseNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NameToken> op3
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mLeft = left;
}

std::shared_ptr<ExpressionNode> ExceptClauseNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> ExceptClauseNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> ExceptClauseNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<NameToken> ExceptClauseNode::GetOperator3()
{
    return mOp3;
}
