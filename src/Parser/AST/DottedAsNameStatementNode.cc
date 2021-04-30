
#include <ast/DottedAsNameStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DottedAsNameStatementNode::DottedAsNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NameToken> op3
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp2 = op2;
    mOp3 = op3;
}
