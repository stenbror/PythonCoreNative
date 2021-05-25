
#include <ast/SingleInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

SingleInputNode::SingleInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> newline,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mNewline = newline;
    mRight = right;
}

std::shared_ptr<Token> SingleInputNode::GetNewline()
{
    return mNewline;
}

std::shared_ptr<StatementNode> SingleInputNode::GetRight()
{
    return mRight;
}
