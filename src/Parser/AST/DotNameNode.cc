
#include <ast/DotNameNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DotNameNode::DotNameNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NameToken> op2
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
}

std::shared_ptr<Token> DotNameNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<NameToken> DotNameNode::GetOperator2()
{
    return mOp2;
}
