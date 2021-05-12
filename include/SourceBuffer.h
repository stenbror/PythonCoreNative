#pragma once

#include <memory>
#include <string>

namespace PythonCoreNative::RunTime::Parser
{

    class SourceBuffer
    {
        public:
            SourceBuffer();

            wchar_t GetChar();
            wchar_t PeekChar();
            void UngetChar(wchar_t ch);
            unsigned int BufferPosition();

            void Next();

            bool IsLiteralStartCharacter();
            bool IsLiteralOrNumberCharacter();
            bool IsHexDigit();
            bool IsOctetDigit();
            bool IsBinaryDigit();
            bool IsDigit();

        protected:

            std::shared_ptr<std::wstring> mSourceCode;
    };
}