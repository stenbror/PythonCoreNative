
#include <ast/AtomFalseNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

AtomFalseNode::AtomFalseNode(unsigned int start, unsigned int end, std::shared_ptr<Token> op1) : ExpressionNode(start, end)
{
    mOp1 = op1;
}
