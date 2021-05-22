#include <Token.h>

using namespace PythonCoreNative::RunTime::Parser;

TypeCommentToken::TypeCommentToken( unsigned int startPosition, 
                                    unsigned int endPosition, 
                                    std::shared_ptr<std::wstring> text,
                                    std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList) 
    :   Token(startPosition, endPosition, TokenKind::TypeComment, triviaList) 
{
    mTypeComment = text;
}

std::shared_ptr<std::wstring> TypeCommentToken::GetTyåeCommentText()
{
    return mTypeComment;
}
