
#include <ast/NonlocalStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

NonlocalStatementNode::NonlocalStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mNodes = nodes;
    mSeparators = separators;
}
