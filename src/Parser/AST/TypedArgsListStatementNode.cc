
#include <ast/TypedArgsListStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
