#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

NumberToken::NumberToken(   unsigned int startPosition, 
                            unsigned int endPosition, 
                            bool isImaginaryNumber,
                            bool isRealNumber,
                            std::shared_ptr<std::wstring> text,
                            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList) 
    :   Token(startPosition, endPosition, TokenKind::Number, triviaList) 
{
    mText = text;
    mIsImaginaryNumber = isImaginaryNumber;
    mIsRealNumber = isRealNumber;
}

bool NumberToken::IsImaginaryNumber()
{
    return mIsImaginaryNumber;
}

bool NumberToken::IsRealNumber()
{
    return mIsRealNumber;
}

std::shared_ptr<std::wstring> NumberToken::GetText()
{
    return mText;
}
