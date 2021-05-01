
#include <ast/TypeInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

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
