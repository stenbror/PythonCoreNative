
#include <ast/MappingPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

MappingPatternNode::MappingPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> openCurly,
                            std::shared_ptr<AST::StatementNode> items,
                            std::shared_ptr<Token> firstComma,
                            std::shared_ptr<AST::StatementNode> doubleStar,
                            std::shared_ptr<Token> secondComma,
                            std::shared_ptr<Token> closeCurly
                        ) : StatementNode(start, end)
{
    
    mOpenCurly = openCurly;
    mItems = items;
    mFirstComma = firstComma;
    mDoubleStar = doubleStar;
    mSecondComma = secondComma;
    mCloseCurly = closeCurly;

}

std::shared_ptr<Token> MappingPatternNode::GetOpenCurly()
{
    return mOpenCurly;
}

std::shared_ptr<AST::StatementNode> MappingPatternNode::GetItems()
{
    return mItems;
}

std::shared_ptr<Token> MappingPatternNode::GetFirstComma()
{
    return mFirstComma;
}

std::shared_ptr<AST::StatementNode> MappingPatternNode::GetDoubleStar()
{
    return mDoubleStar;
}

std::shared_ptr<Token> MappingPatternNode::GetSecondComma()
{
    return mSecondComma;
}

std::shared_ptr<Token> MappingPatternNode::GetCloseCurly()
{
    return mCloseCurly;
}
