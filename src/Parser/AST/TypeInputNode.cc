
#include <ast/TypeInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

TypeInputNode::TypeInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<TypeNode> right,
                            std::shared_ptr<Token> eof
                        ) : TypeNode(start, end)
{
    mNewlines = newlines;
    mRight = right;
    mEof = eof;
}

std::shared_ptr<std::vector<std::shared_ptr<Token>>> TypeInputNode::GetNewlines()
{
    return mNewlines;
}

std::shared_ptr<TypeNode> TypeInputNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> TypeInputNode::GetEof()
{
    return mEof;
}
