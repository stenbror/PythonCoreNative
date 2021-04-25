
#include <ast/AtomNumberNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomNumberNode::AtomNumberNode(unsigned int start, unsigned int end, std::shared_ptr<NumberToken> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}
