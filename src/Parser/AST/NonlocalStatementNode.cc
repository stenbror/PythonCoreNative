
#include <ast/NonlocalStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

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

std::shared_ptr<Token> NonlocalStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> NonlocalStatementNode::GetNodes()
{
    return mNodes;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> NonlocalStatementNode::GetSeparators()
{
    return mSeparators;
}
