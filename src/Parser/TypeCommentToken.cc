#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

TypeCommentToken::TypeCommentToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text) 
    :   Token(startPosition, endPosition, TokenKind::TypeComment) 
{
    mTypeComment = text;
}
