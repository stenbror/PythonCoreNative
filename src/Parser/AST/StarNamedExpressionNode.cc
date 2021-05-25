
#include <ast/StarNamedExpressionNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

StarNamedExpressionNode::StarNamedExpressionNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}

std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> StarNamedExpressionNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> StarNamedExpressionNode::GetSeparators()
{
    return mSeparators;
}

