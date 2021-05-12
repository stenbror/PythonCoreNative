#pragma once

#include <exception>
#include <string>
#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class LexicalError : public std::exception
    {
        public:
            LexicalError(unsigned int position, std::shared_ptr<std::wstring> msg);

        protected:
            unsigned int mPosition;
            std::shared_ptr<std::wstring> mMsg;
    };
}
