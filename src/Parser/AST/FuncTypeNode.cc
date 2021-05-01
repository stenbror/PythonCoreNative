
#include <ast/FuncTypeNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

FuncTypeNode::FuncTypeNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<TypeNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> right
                        ) : TypeNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mOp2 = op2;
    mOp3 = op3;
    mRight = right;
}
