
#include <ast/CaseStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

CaseStatementNode::CaseStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> next
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;
    mNext = next;
}
