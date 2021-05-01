
#include <ast/TypeListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
