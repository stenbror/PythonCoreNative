
#include <ast/DottedAsNameStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DottedAsNameStatementNode::DottedAsNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NameToken> op2
                        ) : StatementNode(start, end)
{
    mLeft = left;
    mOp1 = op1;
    mOp2 = op2;
}

std::shared_ptr<StatementNode> DottedAsNameStatementNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> DottedAsNameStatementNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<NameToken> DottedAsNameStatementNode::GetOperator2()
{
    return mOp2;
}
