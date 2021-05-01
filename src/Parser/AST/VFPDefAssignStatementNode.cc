
#include <ast/VFPDefAssignStatementNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

VFPDefAssignStatementNode::VFPDefAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mOp2 = op2;
    mRight = right;
}
