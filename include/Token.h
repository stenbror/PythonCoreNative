
#pragma once

#include <TokenKind.h>
#include <Trivia.h>

#include <string>
#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser
{
    class Token
    {
        public:
            Token(  unsigned int startPosition, 
                    unsigned int endPosition, 
                    TokenKind kind,
                    std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList);

            TokenKind GetSymbolKind();
            unsigned int GetTokenStartPosition();
            unsigned int GetTokenEndPosition();
            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> GetTriviaList();

        protected:
            TokenKind mKind;
            unsigned int mTokenStartPosition;
            unsigned int mTokenEndPosition;
            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> mTriviaList;

    };

    class NameToken : public Token
    {
        public:
            NameToken(  unsigned int startPosition, 
                        unsigned int endPosition, 
                        std::shared_ptr<std::wstring> text,
                        std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList);

            bool IsCaseSoftKeyword();   /* 'case' */
            bool IsMatchSoftKeyword();  /* 'match' */
            bool IsWildCardPattern();    /* '_' */
            bool IsNotWildCardPrefixed();   /* ! _Name */

            std::shared_ptr<std::wstring> GetText();

        protected:
            std::shared_ptr<std::wstring> mText;
    };

    class NumberToken  : public Token
    {
        public:
            NumberToken(    unsigned int startPosition, 
                            unsigned int endPosition, 
                            bool isImaginaryNumber,
                            bool isRealNumber,
                            std::shared_ptr<std::wstring> text,
                            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList);

            bool IsImaginaryNumber();
            bool IsRealNumber();
            std::shared_ptr<std::wstring> GetText();

        protected:
            std::shared_ptr<std::wstring> mText;
            bool mIsImaginaryNumber;
            bool mIsRealNumber;
    };

    class StringToken : public Token
    {
        public:
            StringToken(    unsigned int startPosition, 
                            unsigned int endPosition, 
                            std::shared_ptr<std::wstring> text,
                            bool isRaw,
                            bool isUnicode,
                            bool isFormated,
                            std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList);

            std::shared_ptr<std::wstring> GetText();
            bool IsRaw();
            bool IsUnicode();
            bool IsFormated();

        protected:
            std::shared_ptr<std::wstring> mText;
            bool mIsRaw;
            bool mIsUnicode;
            bool mIsFormated;
    };

    class TypeCommentToken : public Token
    {
        public:
            TypeCommentToken(   unsigned int startPosition, 
                                unsigned int endPosition, 
                                std::shared_ptr<std::wstring> text,
                                std::shared_ptr<std::vector<std::shared_ptr<Trivia>>> triviaList);

            std::shared_ptr<std::wstring> GetTypeCommentText();

        protected:
            std::shared_ptr<std::wstring> mTypeComment;
    };
}