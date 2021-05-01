
#include <ast/Node.h>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class StatementNode : protected Node
    {
        protected:
            StatementNode(unsigned int start, unsigned int end);

        public:
            bool isExpressionNode() { return false; };
            bool isStatementNode() { return true; };
            bool isTypeNode() { return false; };
    };
}
