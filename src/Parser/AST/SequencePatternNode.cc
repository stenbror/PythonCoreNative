
#include <ast/SequencePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
