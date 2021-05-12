#pragma once

#include <Token.h>

#include <memory>
#include <map>
#include <string>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreTokenizer
    {

        public:
            PythonCoreTokenizer(unsigned int tabSize);

            std::shared_ptr<Token> CurSymbol();
            unsigned int Position();
            void Advance();

        protected:
            std::shared_ptr<Token> mCurSymbol;

            const static inline std::map<std::basic_string<char32_t>, TokenKind> mReservedKeywords
                {
                    { U"False",     TokenKind::PyFalse },
                    { U"None",      TokenKind::PyNone },
                    { U"True",      TokenKind::PyTrue },
                    { U"and",       TokenKind::PyAnd },
                    { U"as",        TokenKind::PyAs },
                    { U"assert",    TokenKind::PyAssert },
                    { U"async",     TokenKind::PyAsync },
                    { U"await",     TokenKind::PyAwait },
                    { U"break",     TokenKind::PyBreak },
                    { U"class",     TokenKind::PyClass },
                    { U"continue",  TokenKind::PyContinue },
                    { U"def",       TokenKind::PyDef },
                    { U"del",       TokenKind::PyDel },
                    { U"elif",      TokenKind::PyElif },
                    { U"else",      TokenKind::PyElse },
                    { U"except",    TokenKind::PyExcept },
                    { U"finally",   TokenKind::PyFinally },
                    { U"for",       TokenKind::PyFor },
                    { U"from",      TokenKind::PyFrom },
                    { U"global",    TokenKind::PyGlobal },
                    { U"if",        TokenKind::PyIf },
                    { U"import",    TokenKind::PyImport },
                    { U"in",        TokenKind::PyIn },
                    { U"is",        TokenKind::PyIs },
                    { U"lambda",    TokenKind::PyLambda },
                    { U"nonlocal",  TokenKind::PyNonLocal },
                    { U"not",       TokenKind::PyNot },
                    { U"or",        TokenKind::PyOr },
                    { U"pass",      TokenKind::PyPass },
                    { U"raise",     TokenKind::PyRaise },
                    { U"return",    TokenKind::PyReturn },
                    { U"try",       TokenKind::PyTry },
                    { U"while",     TokenKind::PyWhile },
                    { U"with",      TokenKind::PyWith },
                    { U"yield",     TokenKind::PyYield }
                };

    };
}