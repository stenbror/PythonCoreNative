#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomNameNode : public ExpressionNode
    {
        public:
            AtomNameNode(unsigned int start, unsigned int end, std::shared_ptr<NameToken> op1);
            std::shared_ptr<NameToken> GetNameText();

        protected:
            std::shared_ptr<NameToken> mOp1;
    };
}
