
#include <ast/WithStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

WithStatementNode::WithStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> withItems,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mRight = right;
    mWithItems = withItems;
    mSeparators = separators;
}
