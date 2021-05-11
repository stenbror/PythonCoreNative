
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

PythonCoreParser::PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer)
{
    mLexer = lexer;
    mFlowLevel = 0;
    mFuncLevel = 0;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseEvalInput()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFileInput()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSingleInput()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncTypeInput()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncType()
{
    auto startPos = mLexer->Position();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyLeftParen )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting '(' in Func!"));

    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ? nullptr : ParseTypeList();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting ')' in Func!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyArrow )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting '->' in Func!"));

    auto symbol3 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseTest();

    return std::make_shared<AST::FuncTypeNode>(startPos, mLexer->Position(), symbol1, left, symbol2, symbol3, right);
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseTypeList()
{
    return nullptr;
}