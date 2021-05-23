
#include <ast/DoubleStarPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DoubleStarPatternNode::DoubleStarPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;

}

std::shared_ptr<Token> DoubleStarPatternNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<AST::StatementNode> DoubleStarPatternNode::GetRight()
{
    return mRight;
}
