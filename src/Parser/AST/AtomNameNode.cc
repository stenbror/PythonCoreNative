
#include <ast/AtomNameNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomNameNode::AtomNameNode(unsigned int start, unsigned int end, std::shared_ptr<NameToken> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}
