
#include <ast/StarPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

StarPatternNode::StarPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    mRight = right;

}
