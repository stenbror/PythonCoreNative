
#include <ast/ClassPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ClassPatternNode::ClassPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots,
                            std::shared_ptr<Token> openCurly,
                            std::shared_ptr<AST::StatementNode> positionals,
                            std::shared_ptr<Token> firstComma,
                            std::shared_ptr<AST::StatementNode> keywords,
                            std::shared_ptr<Token> secondComma,
                            std::shared_ptr<Token> closeCurly
                        ) : StatementNode(start, end)
{
    
    mNodes = nodes;
    mDots = dots;
    mOpenCurly = openCurly;
    mPositionals = positionals;
    mFirstComma = firstComma;
    mKeywords = keywords;
    mSecondComma = secondComma;
    mCloseCurly = closeCurly;

}
