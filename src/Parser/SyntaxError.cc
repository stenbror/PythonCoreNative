
#include <SyntaxError.h>

using namespace PythonCoreNative::RunTime::Parser;

SyntaxError::SyntaxError(unsigned int position, std::shared_ptr<Token> curSymbol, std::shared_ptr<std::wstring> msg)
{
    mPosition = position;
    mSymbol = curSymbol;
    mMsg = msg;
}
