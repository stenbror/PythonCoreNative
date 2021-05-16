
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

// This is the rules for Match statement introduced in Python 3.10

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMatch()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol(); /* Identifier 'match' */
    mLexer->Advance();

    auto left = ParseSubjectExpr();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting ':' in 'match' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting Newline in 'match' statement!"));

    auto symbol3 = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Indent)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting Indent in 'match' statement!"));

    auto symbol4 = mLexer->CurSymbol();
    mLexer->Advance();

    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();

    do
    {
        
        nodes->push_back( ParseCaseBlock() );

    } while (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Dedent);
    
    auto symbol5 = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::MatchStatementNode>(
        startPos,
        mLexer->Position(),
        symbol,     /* 'match' */
        left, 
        symbol2,    /* ':' */
        symbol3,    /* 'NEWLINE' */
        symbol4,    /* 'INDENT' */
        nodes,
        symbol5 );  /* 'DEDENT' */
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSubjectExpr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseCaseBlock()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGuard()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePatterns()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseOrPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseClosedPattern()
{
    return nullptr;
}
std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseLiteralPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseLiteralExpr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseComplexNumber()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSignedNumber()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSignedRealNumber()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseRealNumber()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImaginaryNumber()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseCapturePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePatternCaptureTarget()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseWildCardPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseValuePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAttr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseNameOrAttr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGroupPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSequencePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseOpenSequencePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMaybeeSequencePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMaybeeStarExpr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseStarPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMappingPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseItemsPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseKeyValuePattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDoubleStarPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseClassPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePositionalPattern()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseKeywordPatterns()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseKeywordPattern()
{
    return nullptr;
}
