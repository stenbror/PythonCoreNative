
#include <ast/KeyValuePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

KeyValuePatternNode::KeyValuePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<AST::StatementNode> key,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> value
                        ) : StatementNode(start, end)
{
    
    mKey = key;
    mOp1 = op1;
    mValue = value;

}
