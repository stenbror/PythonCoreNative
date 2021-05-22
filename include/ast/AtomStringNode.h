#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomStringNode : public ExpressionNode
    {
        public:
            AtomStringNode(unsigned int start, unsigned int end, std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> ops);
            std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> GetStringNodes();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<StringToken>>> mOps;
    };
}
