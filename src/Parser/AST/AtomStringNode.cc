
#include <ast/AtomStringNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomStringNode::AtomStringNode(unsigned int start, unsigned int end, std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> ops) : ExpressionNode(start, end)
{
    mOps = ops;
}
