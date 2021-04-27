
#include <ast/SimpleStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

SimpleStatementNode::SimpleStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> op1
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mNodes = nodes;
    mSeparators = separators;
}
