
#include <ast/DictionaryContainerNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DictionaryContainerNode::DictionaryContainerNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> entries,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mEntries = entries;
    mSeparators = separators;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> DictionaryContainerNode::GetEntries()
{
    return mEntries;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> DictionaryContainerNode::GetSeparators()
{
    return mSeparators;
}
