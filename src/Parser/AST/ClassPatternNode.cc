
#include <ast/ClassPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

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

std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> ClassPatternNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> ClassPatternNode::GetDots()
{
    return mDots;
}

std::shared_ptr<Token> ClassPatternNode::GetOpenCurly()
{
    return mOpenCurly;
}

std::shared_ptr<AST::StatementNode> ClassPatternNode::GetPositionals()
{
    return mPositionals;
}

std::shared_ptr<Token> ClassPatternNode::GetFirstComma()
{
    return mFirstComma;
}

std::shared_ptr<AST::StatementNode> ClassPatternNode::GetKeywords()
{
    return mKeywords;
}

std::shared_ptr<Token> ClassPatternNode::GetSecondComma()
{
    return mSecondComma;
}

std::shared_ptr<Token> ClassPatternNode::GetCloseCurly()
{
    return mCloseCurly;
}
