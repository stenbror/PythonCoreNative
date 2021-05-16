
#include <ast/StarNamedExpressionNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

StarNamedExpressionNode::StarNamedExpressionNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : ExpressionNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
