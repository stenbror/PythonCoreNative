#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomNumberNode : public ExpressionNode
    {
        public:
            AtomNumberNode(unsigned int start, unsigned int end, std::shared_ptr<NumberToken> op1);
            std::shared_ptr<NumberToken> GetNumberText();

        protected:
            std::shared_ptr<NumberToken> mOp1;
    };
}
