#pragma once

#include <Token.h>
#include <SourceBuffer.h>
#include <LexicalError.h>

#include <memory>
#include <map>
#include <string>
#include <sstream>
#include <stack>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreTokenizer
    {

        public:
            PythonCoreTokenizer(unsigned int tabSize, std::shared_ptr<SourceBuffer> sourceBuffer);

            std::shared_ptr<Token> CurSymbol();
            unsigned int Position();
            void Advance();

        protected:
            std::shared_ptr<Token> mCurSymbol;

            const static inline std::map<std::wstring, TokenKind> mReservedKeywords
                {
                    { L"False",     TokenKind::PyFalse },
                    { L"None",      TokenKind::PyNone },
                    { L"True",      TokenKind::PyTrue },
                    { L"and",       TokenKind::PyAnd },
                    { L"as",        TokenKind::PyAs },
                    { L"assert",    TokenKind::PyAssert },
                    { L"async",     TokenKind::PyAsync },
                    { L"await",     TokenKind::PyAwait },
                    { L"break",     TokenKind::PyBreak },
                    { L"class",     TokenKind::PyClass },
                    { L"continue",  TokenKind::PyContinue },
                    { L"def",       TokenKind::PyDef },
                    { L"del",       TokenKind::PyDel },
                    { L"elif",      TokenKind::PyElif },
                    { L"else",      TokenKind::PyElse },
                    { L"except",    TokenKind::PyExcept },
                    { L"finally",   TokenKind::PyFinally },
                    { L"for",       TokenKind::PyFor },
                    { L"from",      TokenKind::PyFrom },
                    { L"global",    TokenKind::PyGlobal },
                    { L"if",        TokenKind::PyIf },
                    { L"import",    TokenKind::PyImport },
                    { L"in",        TokenKind::PyIn },
                    { L"is",        TokenKind::PyIs },
                    { L"lambda",    TokenKind::PyLambda },
                    { L"nonlocal",  TokenKind::PyNonLocal },
                    { L"not",       TokenKind::PyNot },
                    { L"or",        TokenKind::PyOr },
                    { L"pass",      TokenKind::PyPass },
                    { L"raise",     TokenKind::PyRaise },
                    { L"return",    TokenKind::PyReturn },
                    { L"try",       TokenKind::PyTry },
                    { L"while",     TokenKind::PyWhile },
                    { L"with",      TokenKind::PyWith },
                    { L"yield",     TokenKind::PyYield }
                };

            std::shared_ptr<SourceBuffer> mSourceBuffer;
            unsigned int mPosition;
            bool mAtBOL;
            bool mIsBlankLine;
            int mPending;
            unsigned int mTabSize;

            std::stack<TokenKind> mLevelStack;
            std::stack<unsigned int> mIndentLevel;

    };
}