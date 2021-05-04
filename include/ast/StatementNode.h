#pragma once

#include <ast/Node.h>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class StatementNode : public Node
    {
        protected:
            StatementNode(unsigned int start, unsigned int end);

        public:
            bool isExpressionNode() { return false; };
            bool isStatementNode() { return true; };
            bool isTypeNode() { return false; };
    };
}
