
#include <ast/SequencePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SequencePatternNode::SequencePatternNode(  
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

std::shared_ptr<Token> SequencePatternNode::GetOperator1()
{
    return mOp1;
}

std::shared_ptr<AST::StatementNode> SequencePatternNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> SequencePatternNode::GetOperator2()
{
    return mOp2;
}
