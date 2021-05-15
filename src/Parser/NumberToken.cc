#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

NumberToken::NumberToken(   unsigned int startPosition, 
                            unsigned int endPosition, 
                            std::shared_ptr<std::wstring> text,
                            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList) 
    :   Token(startPosition, endPosition, TokenKind::Number, triviaList) 
{
    mText = text;
}
