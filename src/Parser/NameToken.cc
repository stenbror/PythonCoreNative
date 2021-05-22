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
    return mText->find_first_of(L"case", 0, sizeof(wchar_t)) && mText->size() == 4;
}

bool NameToken::IsMatchSoftKeyword()
{
    return mText->find_first_of(L"match", 0, sizeof(wchar_t)) && mText->size() == 5;
}

bool NameToken::IsWildCardPattern()
{
    return mText->find_first_of(L"_", 0, sizeof(wchar_t)) && mText->size() == 1;
}

bool NameToken::IsNotWildCardPrefixed()
{
    return !mText->find_first_of(L"_", 0, sizeof(wchar_t));
}

std::shared_ptr<std::wstring> NameToken::GetText()
{
    return mText;
}
