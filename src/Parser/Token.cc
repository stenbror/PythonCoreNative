#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

Token::Token(unsigned int startPosition, unsigned int endPosition, TokenKind kind)
{
    mTokenStartPosition = startPosition;
    mTokenEndPosition = endPosition;
    mKind = kind;
}

TokenKind Token::GetSymbolKind()
{
    return mKind;
}    