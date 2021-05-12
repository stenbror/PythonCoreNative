#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

NameToken::NameToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text) 
    :   Token(startPosition, endPosition, TokenKind::Name) 
{
    mText = text;
}
