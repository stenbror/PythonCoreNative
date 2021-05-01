
#include <ast/FileInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

FileInputNode::FileInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> eof
                        ) : StatementNode(start, end)
{
    mNewlines = newlines;
    mNodes = nodes;
    mEof = eof;
}
