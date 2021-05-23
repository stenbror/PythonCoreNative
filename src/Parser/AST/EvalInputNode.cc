
#include <ast/EvalInputNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

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

std::shared_ptr<std::vector<std::shared_ptr<Token>>> EvalInputNode::GetNewlines()
{
    return mNewlines;
}

std::shared_ptr<ExpressionNode> EvalInputNode::GetRight()
{
    return mRight;
}

std::shared_ptr<Token> EvalInputNode::GetEof()
{
    return mEof;
}
