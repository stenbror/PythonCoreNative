
#include <ast/ValuePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

ValuePatternNode::ValuePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots
                        ) : StatementNode(start, end)
{
    
    mNodes = nodes;
    mDots = dots;

}

std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> ValuePatternNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> ValuePatternNode::GetDots()
{
    return mDots;
}
