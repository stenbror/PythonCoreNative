
#include <ast/AtomElipsisNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomElipsisNode::AtomElipsisNode(unsigned int start, unsigned int end, std::shared_ptr<Token> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}
