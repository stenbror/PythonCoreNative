
#include <ast/ExceptClauseNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ExceptClauseNode::ExceptClauseNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NameToken> op3
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
    mLeft = left;
}
