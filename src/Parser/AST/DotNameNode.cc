
#include <ast/DotNameNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

DotNameNode::DotNameNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NameToken> op2
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
}
