
#include <ast/DictionaryEntryNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
