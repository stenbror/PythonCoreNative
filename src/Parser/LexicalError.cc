
#include <LexicalError.h>

using namespace PythonCoreNative::RunTime::Parser;

LexicalError::LexicalError(unsigned int position, std::shared_ptr<std::wstring> msg)
{
    mPosition = position;
    mMsg = msg;
}

std::shared_ptr<std::wstring> LexicalError::ExceptionText()
{
    return mMsg;
}

unsigned int LexicalError::ExceptionPosition()
{
    return mPosition;
}
