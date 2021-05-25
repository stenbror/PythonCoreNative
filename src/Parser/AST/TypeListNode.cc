
#include <ast/TypeListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TypeListNode::TypeListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<ExpressionNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<ExpressionNode> powerNode
                        ) : TypeNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
    mMul = mul;
    mMulNode = mulNode;
    mPower = power;
    mPowerNode = powerNode;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> TypeListNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> TypeListNode::GetSeparators()
{
    return mSeparators;
}

std::shared_ptr<Token> TypeListNode::GetMul()
{
    return mMul;
}

std::shared_ptr<ExpressionNode> TypeListNode::GetMulNode()
{
    return mMulNode;
}
std::shared_ptr<Token> TypeListNode::GetPower()
{
    return mPower;
}

std::shared_ptr<ExpressionNode> TypeListNode::GetPowerNode()
{
    return mPowerNode;
}
