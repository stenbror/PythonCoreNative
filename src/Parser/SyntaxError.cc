
#include <SyntaxError.h>

using namespace PythonCoreNative::RunTime::Parser;

SyntaxError::SyntaxError(unsigned int position, std::shared_ptr<Token> curSymbol, std::shared_ptr<std::wstring> msg)
{
    mPosition = position;
    mSymbol = curSymbol;
    mMsg = msg;
}

unsigned int SyntaxError::GetPosition()
{
    return mPosition;
}

std::shared_ptr<Token> SyntaxError::GetFailureSymbol()
{
    return mSymbol;
}

std::shared_ptr<std::wstring> SyntaxError::GetExceptionText()
{
    return mMsg;
}
