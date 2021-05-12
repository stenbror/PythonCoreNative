
#include <LexicalError.h>

using namespace PythonCoreNative::RunTime::Parser;

LexicalError::LexicalError(unsigned int position, std::shared_ptr<std::wstring> msg)
{
    mPosition = position;
    mMsg = msg;
}
