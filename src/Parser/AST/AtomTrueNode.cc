
#include <ast/AtomTrueNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomTrueNode::AtomTrueNode(unsigned int start, unsigned int end, std::shared_ptr<Token> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<Token> AtomTrueNode::GetOperator()
{
    return mOp1;
}
