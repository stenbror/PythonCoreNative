
#include <ast/GroupPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

GroupPatternNode::GroupPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right,
                            std::shared_ptr<Token> op2
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;
    mOp2 = op2;

}

std::shared_ptr<Token> GroupPatternNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<AST::StatementNode> GroupPatternNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> GroupPatternNode::GetOperator2()
{
    return mOp2;
}
