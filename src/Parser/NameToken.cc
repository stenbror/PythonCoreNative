#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

NameToken::NameToken(   unsigned int startPosition, 
                        unsigned int endPosition, 
                        std::shared_ptr<std::wstring> text,
                        std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList) 
    :   Token(startPosition, endPosition, TokenKind::Name, triviaList) 
{
    mText = text;
}
