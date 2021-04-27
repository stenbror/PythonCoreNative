
#include <ast/ExceptNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

ExceptNode::ExceptNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        ) : StatementNode(start, end)
{
    mOp1 = op1;
    mLeft = left;
    mRight = right;
}
