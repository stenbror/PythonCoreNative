
#include <ast/AtomStringNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomStringNode::AtomStringNode(unsigned int start, unsigned int end, std::shared_ptr<std::vector<StringToken>> ops) : ExpressionNode(start, end)
{
    mOps = ops;
}
