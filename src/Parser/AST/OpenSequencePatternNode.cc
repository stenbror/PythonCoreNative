
#include <ast/OpenSequencePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
