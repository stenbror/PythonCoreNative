
#include <ast/DictionaryKWEntryNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

DictionaryKWEntryNode::DictionaryKWEntryNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> value
                        ) : ExpressionNode(start, end)
{
    mOp1 = op1;
    mValue = value;
}

std::shared_ptr<Token> DictionaryKWEntryNode::GetOperator()
{
    return mOp1;
}

std::shared_ptr<ExpressionNode> DictionaryKWEntryNode::GetValue()
{
    return mValue;
}
