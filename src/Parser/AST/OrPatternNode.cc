
#include <ast/OrPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

OrPatternNode::OrPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    
    mNodes = nodes;
    mSeparators = separators;

}

std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> OrPatternNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> OrPatternNode::GetSeparators()
{
    return mSeparators;
}
