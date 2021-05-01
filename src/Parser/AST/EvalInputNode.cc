
#include <ast/EvalInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

EvalInputNode::EvalInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> eof
                        ) : StatementNode(start, end)
{
    mNewlines = newlines;
    mRight = right;
    mEof = eof;
}
