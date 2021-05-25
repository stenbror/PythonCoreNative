
#include <ast/TypedArgsListStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TypedArgsListStatementNode::TypedArgsListStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<StatementNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<StatementNode> powerNode,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> typeComment
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
    mSlash = slash;
    mMul = mul;
    mMulNode = mulNode;
    mPower = power;
    mPowerNode = powerNode;
    mTypeComment = typeComment;
}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> TypedArgsListStatementNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> TypedArgsListStatementNode::GetSeparators()
{
    return mSeparators;
}

std::shared_ptr<Token> TypedArgsListStatementNode::GetSlash()
{
    return mSlash;
}

std::shared_ptr<Token> TypedArgsListStatementNode::GetMul()
{
    return mMul;
}

std::shared_ptr<StatementNode> TypedArgsListStatementNode::GetMulNode()
{
    return mMulNode;
}

std::shared_ptr<Token> TypedArgsListStatementNode::GetPower()
{
    return mPower;
}

std::shared_ptr<StatementNode> TypedArgsListStatementNode::GetPowerNode()
{
    return mPowerNode;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> TypedArgsListStatementNode::GetTypeComment()
{
    return mTypeComment;
}

