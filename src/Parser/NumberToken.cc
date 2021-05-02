#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

NumberToken::NumberToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::basic_string<char32_t>> text) 
    :   Token(startPosition, endPosition, TokenKind::Number) 
{
    mText = text;
}
