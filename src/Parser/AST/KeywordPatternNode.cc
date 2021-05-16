
#include <ast/KeywordPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
