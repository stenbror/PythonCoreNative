
#include <ast/ArgsListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ArgsListNode::ArgsListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> ArgsListNode::GetNodes()
{
    return mNodes;
} 

std::shared_ptr<std::vector<std::shared_ptr<Token>>> ArgsListNode::GetSeparators()
{
    return mSeparators;
}
