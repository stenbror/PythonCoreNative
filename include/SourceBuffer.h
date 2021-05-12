#pragma once

#include <memory>
#include <string>

namespace PythonCoreNative::RunTime::Parser
{

    class SourceBuffer
    {
        public:
            SourceBuffer();

            char32_t GetChar();
            void UngetChar(char32_t ch);

            bool inline IsLiteralStartCharacter(char32_t ch);
            bool inline IsLiteralOrNumberCharacter(char32_t ch);
            bool inline IsHexDigit(char32_t ch);
            bool inline IsOctetDigit(char32_t ch);
            bool inline IsBinaryDigit(char32_t ch);
            bool inline IsDigit(char32_t ch);

        protected:

            std::shared_ptr<std::basic_string<char32_t>> mSourceCode;
    };
}
