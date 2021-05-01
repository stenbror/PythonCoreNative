
#include <ast/Node.h>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ExpressionNode : protected Node
    {
        protected:
            ExpressionNode(unsigned int start, unsigned int end);

        public:
            bool isExpressionNode() { return true; };
            bool isStatementNode() { return false; };
            bool isTypeNode() { return false; };
    };
}
