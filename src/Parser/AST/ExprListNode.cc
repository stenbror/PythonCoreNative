
#include <ast/ExprListNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ExprListNode::ExprListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
