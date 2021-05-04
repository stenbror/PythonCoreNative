
#include <ast/VarArgsListExpressionNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
