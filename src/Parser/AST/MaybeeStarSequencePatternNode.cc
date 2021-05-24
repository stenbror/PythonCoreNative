
#include <ast/MaybeeStarSequencePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

MaybeeStarSequencePatternNode::MaybeeStarSequencePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    
    mNodes = nodes;
    mSeparators = separators;

}

std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> MaybeeStarSequencePatternNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> MaybeeStarSequencePatternNode::GetSeparators()
{
    return mSeparators;
}
