#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

Token::Token(unsigned int startPosition, unsigned int endPosition, TokenKind kind, std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList)
{
    mTokenStartPosition = startPosition;
    mTokenEndPosition = endPosition;
    mKind = kind;
    mTriviaList = triviaList;
}

TokenKind Token::GetSymbolKind()
{
    return mKind;
}   

unsigned int Token::GetTokenStartPosition()
{
    return mTokenStartPosition;
}

unsigned int Token::GetTokenEndPosition()
{
    return mTokenEndPosition;
}

std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> Token::GetTriviaList()
{
    return mTriviaList;
}
