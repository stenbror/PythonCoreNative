
#include <ast/AtomStringNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomStringNode::AtomStringNode(unsigned int start, unsigned int end, std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> ops) : ExpressionNode(start, end)
{
    mOps = ops;
}

std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> AtomStringNode::GetStringNodes()
{
    return mOps;
}
