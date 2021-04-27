
#include <ast/TryStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

TryStatementNode::TryStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> exceptNodes,
                            std::shared_ptr<StatementNode> elseNode,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mRight = right;
    mOp3 = op3;
    mOp4 = op4;
    mExceptNodes = exceptNodes;
    mElseNode = elseNode;
}
