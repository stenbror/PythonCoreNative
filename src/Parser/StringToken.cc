#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

StringToken::StringToken(   unsigned int startPosition, 
                            unsigned int endPosition, 
                            std::shared_ptr<std::wstring> text,
                            bool isRaw,
                            bool isUnicode,
                            bool isFormated,
                            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList) 
    :   Token(startPosition, endPosition, TokenKind::String, triviaList) 
{
    mText = text;
    mIsRaw = isRaw;
    mIsUnicode = isUnicode;
    mIsFormated = isFormated;
}

std::shared_ptr<std::wstring> StringToken::GetText()
{
    return mText;
}

bool StringToken::IsRaw()
{
    return mIsRaw;
}

bool StringToken::IsUnicode()
{
    return mIsUnicode;
}

bool StringToken::IsFormated()
{
    return mIsFormated;
}
