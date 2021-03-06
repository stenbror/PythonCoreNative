#pragma once

#include <ast/Node.h>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TypeNode : public Node
    {
        protected:
            TypeNode(unsigned int start, unsigned int end);

        public:
            bool isExpressionNode() { return false; };
            bool isStatementNode() { return false; };
            bool isTypeNode() { return true; };

    };
}
