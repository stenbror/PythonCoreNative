
#include <ast/ImportAsNameStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ImportAsNameStatementNode::ImportAsNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mOp3 = op3;
}
