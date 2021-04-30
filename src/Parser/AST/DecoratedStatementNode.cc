
#include <ast/DecoratedStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DecoratedStatementNode::DecoratedStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mRight = right;
}
