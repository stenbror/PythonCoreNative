
#include <ast/SetContainerNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

SetContainerNode::SetContainerNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> entries,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mEntries = entries;
    mSeparators = separators;
}
