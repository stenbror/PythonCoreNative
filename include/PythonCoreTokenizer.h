#pragma once

#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreTokenizer
    {

        public:
            PythonCoreTokenizer(unsigned int tabSize);

            std::shared_ptr<Token> CurSymbol();
            unsigned int Position();
            void Advance();

        protected:
            std::shared_ptr<Token> mCurSymbol;
    };
}