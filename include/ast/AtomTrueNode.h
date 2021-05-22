#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomTrueNode : public ExpressionNode
    {
        public:
            AtomTrueNode(unsigned int start, unsigned int end, std::shared_ptr<Token> op1);
            std::shared_ptr<Token> GetOperator();

        protected:
            std::shared_ptr<Token> mOp1;
    };
}
