#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

StringToken::StringToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::vector<std::shared_ptr<std::basic_string<char32_t>>>> text) 
    :   Token(startPosition, endPosition, TokenKind::String) 
{
    mText = text;
}
