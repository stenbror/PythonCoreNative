
#include <SyntaxError.h>

using namespace PythonCoreNative::RunTime::Parser;

SyntaxError::SyntaxError(unsigned int position, std::shared_ptr<Token> curSymbol, std::shared_ptr<std::basic_string<char32_t>> msg)
{
    mPosition = position;
    mSymbol = curSymbol;
    mMsg = msg;
}
