
#include <ast/LiteralPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

LiteralPatternNode::LiteralPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;

}

TokenKind LiteralPatternNode::LiteralPatternType()
{
    return mOp1->GetSymbolKind();
}
