
#include <Trivia.h>

using namespace PythonCoreNative::RunTime::Parser;

Trivia::Trivia(unsigned int startPosition, unsigned int endPosition)
{
    mTriviaStartPosition = startPosition;
    mTriviaEndPosition = endPosition;
}

NewLineTrivia::NewLineTrivia(unsigned int startPosition, unsigned int endPosition, wchar_t ch1, wchar_t ch2)
    :   Trivia(startPosition, endPosition)
    {
        mChar1 = ch1;
        mChar2 = ch2;
    }

LineContinuationTrivia::LineContinuationTrivia(unsigned int startPosition, unsigned int endPosition)
    :   Trivia(startPosition, endPosition)
    {}

WhiteSpaceTrivia::WhiteSpaceTrivia(unsigned int startPosition, unsigned int endPosition, wchar_t ch)
    : Trivia(startPosition, endPosition)
    {
        mSpaceChar = ch;
    }

CommentTrivia::CommentTrivia(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text)
    : Trivia(startPosition, endPosition)
    {
        mCommentText = text;
    }
