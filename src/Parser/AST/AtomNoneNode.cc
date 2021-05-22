
#include <ast/AtomNoneNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomNoneNode::AtomNoneNode(unsigned int start, unsigned int end, std::shared_ptr<Token> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<Token> AtomNoneNode::GetOperator()
{
    return mOp1;
}
