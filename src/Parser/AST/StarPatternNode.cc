
#include <ast/StarPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

StarPatternNode::StarPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;

}

std::shared_ptr<Token> StarPatternNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<AST::StatementNode> StarPatternNode::GetRight()
{
    return mRight;
}
