
#include <ast/KeywordPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

KeywordPatternNode::KeywordPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<AST::StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}

std::shared_ptr<NameToken> KeywordPatternNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<Token> KeywordPatternNode::GetOperator2()
{
    return mOp2;
}

std::shared_ptr<AST::StatementNode> KeywordPatternNode::GetRight()
{
    return mRight;
}
