
#include <ast/AsPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AsPatternNode::AsPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mLeft = left;
    mOp1 = op1;
    mRight = right;

}

std::shared_ptr<StatementNode> AsPatternNode::GetLeft()
{
    return mLeft;
}

std::shared_ptr<Token> AsPatternNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<StatementNode> AsPatternNode::GetRight()
{
    return mRight;
}
