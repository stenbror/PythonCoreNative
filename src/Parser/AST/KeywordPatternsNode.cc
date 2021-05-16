
#include <ast/KeywordPatternsNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

KeywordPatternsNode::KeywordPatternsNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
