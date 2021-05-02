#pragma once

#include <PythonCoreTokenizer.h>

#include <ast/ExpressionNode.h>
#include <ast/StatementNode.h>


#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreParser
    {
        public:
            PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer);

        protected:
            std::shared_ptr<AST::ExpressionNode> ParseAtom();

        protected:
            std::shared_ptr<PythonCoreTokenizer> mLexer;
    };
}
