
#include <ast/WithStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

WithStatementNode::WithStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> openParenthesis,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> withItems,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> closeParenthesis,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mRight = right;
    mWithItems = withItems;
    mSeparators = separators;
    mOpenParenthesis = openParenthesis;
    mCloseParenthesis = closeParenthesis;
}

std::shared_ptr<Token> WithStatementNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> WithStatementNode::GetOpenParenthesis()
{
    return mOpenParenthesis;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> WithStatementNode::GetWithItems()
{
    return mWithItems;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> WithStatementNode::GetSeparators()
{
    return mSeparators;
}

std::shared_ptr<Token> WithStatementNode::GetCloseParenthesis()
{
    return mCloseParenthesis;
}

std::shared_ptr<Token> WithStatementNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<Token> WithStatementNode::GetOperator3()
{
    return mOp3;
}

std::shared_ptr<StatementNode> WithStatementNode::GetRight()
{
    return mRight;
}
