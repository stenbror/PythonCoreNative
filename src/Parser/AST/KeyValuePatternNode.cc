
#include <ast/KeyValuePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

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

std::shared_ptr<AST::StatementNode> KeyValuePatternNode::GetKey()
{
    return mKey;
}

std::shared_ptr<Token> KeyValuePatternNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<AST::StatementNode> KeyValuePatternNode::GetValue()
{
    return mValue;
}
