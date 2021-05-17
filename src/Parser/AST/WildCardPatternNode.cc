
#include <ast/WildCardPatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

WildCardPatternNode::WildCardPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;
    
}
