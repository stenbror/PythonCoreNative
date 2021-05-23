
#include <ast/DictionaryEntryNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DictionaryEntryNode::DictionaryEntryNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> key,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> value
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mKey = key;
    mValue = value;
}

std::shared_ptr<ExpressionNode> DictionaryEntryNode::GetKey()
{
    return mKey;
}

std::shared_ptr<Token> DictionaryEntryNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> DictionaryEntryNode::GetValue()
{
    return mValue;
}
