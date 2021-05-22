
#include <ast/AtomNumberNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomNumberNode::AtomNumberNode(unsigned int start, unsigned int end, std::shared_ptr<NumberToken> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<NumberToken> AtomNumberNode::GetNumberText()
{
    return mOp1;
}
