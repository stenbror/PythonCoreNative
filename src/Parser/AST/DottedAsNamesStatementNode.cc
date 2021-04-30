
#include <ast/DottedAsNamesStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DottedAsNamesStatementNode::DottedAsNamesStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
