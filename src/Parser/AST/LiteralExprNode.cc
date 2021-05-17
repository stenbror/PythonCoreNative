
#include <ast/LiteralExprNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

LiteralExprNode::LiteralExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;

}

TokenKind LiteralExprNode::LiteralExprType()
{
    return mOp1->GetSymbolKind();
}
