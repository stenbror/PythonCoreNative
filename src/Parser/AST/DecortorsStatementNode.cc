
#include <ast/DecoratorsStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DecoratorsStatementNode::DecoratorsStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
}
