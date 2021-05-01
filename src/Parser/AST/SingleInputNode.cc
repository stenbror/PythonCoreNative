
#include <ast/SingleInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

SingleInputNode::SingleInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> newline,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mNewline = newline;
    mRight = right;
}
