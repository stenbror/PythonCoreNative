
#include <ast/OpenSequencePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

OpenSequencePatternNode::OpenSequencePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    
    mNodes = nodes;
    mSeparators = separators;

}

bool OpenSequencePatternNode::IsGroupPattern()
{
    return mNodes->size() == 1 && mSeparators->size() == 0;
}

std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> OpenSequencePatternNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> OpenSequencePatternNode::GetSeparators()
{
    return mSeparators;
}
