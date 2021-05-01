
#include <ast/VarArgsListStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

VarArgsListStatementNode::VarArgsListStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<StatementNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<StatementNode> powerNode
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
    mSlash = slash;
    mMul = mul;
    mMulNode = mulNode;
    mPower = power;
    mPowerNode = powerNode;
}
