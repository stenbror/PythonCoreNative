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

bool NameToken::IsCaseSoftKeyword()
{

    return mText->size() == 4 && mText->at(0) == L'c' && mText->at(1) == L'a' && mText->at(2) == L's' && 
        mText->at(3) == L'e';

}

bool NameToken::IsMatchSoftKeyword()
{

    return mText->size() == 5 && mText->at(0) == L'm' && mText->at(1) == L'a' && mText->at(2) == L't' && 
        mText->at(3) == L'c' && mText->at(4) == L'h';

}

bool NameToken::IsWildCardPattern()
{

    return mText->size() == 1 && mText->at(0) == L'_';

}

bool NameToken::IsNotWildCardPrefixed()
{

    return !IsWildCardPattern();

}

std::shared_ptr<std::wstring> NameToken::GetText()
{
    return mText;
}
