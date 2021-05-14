#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

StringToken::StringToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text) 
    :   Token(startPosition, endPosition, TokenKind::String) 
{
    mText = text;
}
