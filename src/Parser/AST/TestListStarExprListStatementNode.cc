
#include <ast/TestListStarExprListStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

TestListStarExprListStatementNode::TestListStarExprListStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
