
#include <ast/SuiteStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

SuiteStatementNode::SuiteStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> op3
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mNodes = nodes;
    mOp3 = op3;
}
