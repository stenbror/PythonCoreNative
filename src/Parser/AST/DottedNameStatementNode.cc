
#include <ast/DottedNameStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DottedNameStatementNode::DottedNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    mNodes = nodes;
    mSeparators = separators;
}
