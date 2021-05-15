
#pragma once


#include <string>
#include <memory>

namespace PythonCoreNative::RunTime::Parser
{

    class Trivia
    {
        public:
            Trivia(unsigned int startPosition, unsigned int endPosition);

        protected:
            unsigned int mTriviaStartPosition;
            unsigned int mTriviaEndPosition;

    };

    class NewLineTrivia : public Trivia
    {
        public:
            NewLineTrivia(  unsigned int startPosition, 
                            unsigned int endPosition, 
                            wchar_t ch1, 
                            wchar_t ch2);

        protected:
            wchar_t mChar1, mChar2;
    };

    class LineContinuationTrivia : public Trivia
    {
        public:
            LineContinuationTrivia(unsigned int startPosition, unsigned int endPosition);
            
    };

    class WhiteSpaceTrivia : public Trivia
    {
        public:
            WhiteSpaceTrivia(unsigned int startPos, unsigned int endPosition, wchar_t ch);

        protected:
            wchar_t mSpaceChar;
    };

    class CommentTrivia : public Trivia
    {
        public:
            CommentTrivia(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text);

        protected:
            std::shared_ptr<std::wstring> mCommentText;
    };

}
