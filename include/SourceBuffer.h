#pragma once

#include <memory>
#include <string>
#include <stdexcept>

namespace PythonCoreNative::RunTime::Parser
{

    class SourceBuffer
    {
        public:
            SourceBuffer(std::shared_ptr<std::wstring> buf);

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
            unsigned int mIndex;
    };
}
