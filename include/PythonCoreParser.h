#pragma once

#include <PythonCoreTokenizer.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreParser
    {
        public:
            PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer);

        protected:
            std::shared_ptr<PythonCoreTokenizer> mLexer;
    };
}
