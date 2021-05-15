
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
            Token(unsigned int startPosition, unsigned int endPosition, TokenKind kind);
            TokenKind GetSymbolKind();

        protected:
            TokenKind mKind;
            unsigned int mTokenStartPosition;
            unsigned int mTokenEndPosition;
    };

    class NameToken : public Token
    {
        public:
            NameToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text);

        protected:
            std::shared_ptr<std::wstring> mText;
    };

    class NumberToken  : public Token
    {
        public:
            NumberToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text);

        protected:
            std::shared_ptr<std::wstring> mText;
    };

    class StringToken : public Token
    {
        public:
            StringToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text);

        protected:
            std::shared_ptr<std::wstring> mText;
    };

    class TypeCommentToken : public Token
    {
        public:
            TypeCommentToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::wstring> text);

        protected:
            std::shared_ptr<std::wstring> mTypeComment;
    };
}