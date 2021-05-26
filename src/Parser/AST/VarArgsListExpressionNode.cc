
#include <ast/VarArgsListExpressionNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

VarArgsListExpressionNode::VarArgsListExpressionNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<NameToken> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<NameToken> powerNode
                        ) : ExpressionNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
    mSlash = slash;
    mMul = mul;
    mMulNode = mulNode;
    mPower = power;
    mPowerNode = powerNode;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> VarArgsListExpressionNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> VarArgsListExpressionNode::GetSeparators()
{
    return mSeparators;
}

std::shared_ptr<Token> VarArgsListExpressionNode::GetSlash()
{
    return mSlash;
}

std::shared_ptr<Token> VarArgsListExpressionNode::GetMul()
{
    return mMul;
}

std::shared_ptr<NameToken> VarArgsListExpressionNode::GetMulNode()
{
    return mMulNode;
}

std::shared_ptr<Token> VarArgsListExpressionNode::GetPower()
{
    return mPower;
}

std::shared_ptr<NameToken> VarArgsListExpressionNode::GetPowerNode()
{
    return mPowerNode;
}
