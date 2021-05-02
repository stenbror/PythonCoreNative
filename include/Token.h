
#pragma once

#include <TokenKind.h>

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
            NameToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::basic_string<char32_t>> text);

        protected:
            std::shared_ptr<std::basic_string<char32_t>> mText;
    };

    class NumberToken  : public Token
    {
        public:
            NumberToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::basic_string<char32_t>> text);

        protected:
            std::shared_ptr<std::basic_string<char32_t>> mText;
    };

    class StringToken : public Token
    {
        public:
            StringToken(unsigned int startPosition, unsigned int endPosition, std::shared_ptr<std::vector<std::shared_ptr<std::basic_string<char32_t>>>> text);

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<std::basic_string<char32_t>>>> mText;
    };
}