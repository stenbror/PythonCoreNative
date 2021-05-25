
#include <ast/SetContainerNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SetContainerNode::SetContainerNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> entries,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mEntries = entries;
    mSeparators = separators;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> SetContainerNode::GetEntries()
{
    return mEntries;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> SetContainerNode::GetSeparators()
{
    return mSeparators;
}
