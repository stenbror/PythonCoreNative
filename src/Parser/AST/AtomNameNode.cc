
#include <ast/AtomNameNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

AtomNameNode::AtomNameNode(unsigned int start, unsigned int end, std::shared_ptr<NameToken> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}

std::shared_ptr<NameToken> AtomNameNode::GetNameText()
{
    return mOp1;
}
