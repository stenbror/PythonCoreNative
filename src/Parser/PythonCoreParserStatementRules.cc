
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseCompound()
{
    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyIf:
            return ParseIf();
        case TokenKind::PyFor:
            return ParseFor();
        case TokenKind::PyWhile:
            return ParseWhile();
        case TokenKind::PyWith:
            return ParseWith();
        case TokenKind::PyTry:
            return ParseTry();
        case TokenKind::PyDef:
            return ParseFuncDef();
        case TokenKind::PyClass:
            return ParseClass();
        case TokenKind::PyAsync:
            return ParseAsync();
        case TokenKind::PyMatrice:
            return ParseDecorated();
        default:
            return nullptr; // Should never happend! 
    }
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseIf()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    std::shared_ptr<AST::StatementNode> node = nullptr;

    auto left = ParseNamedExpr();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'if' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElif) nodes->push_back( ParseElif() );

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElse) node = ParseElse();

    return std::make_shared<AST::IfStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right, nodes,node);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseElif()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = ParseNamedExpr();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyElif)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'elif' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();

    return std::make_shared<AST::ElifStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseElse()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyElif)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'else' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();

    return std::make_shared<AST::ElseStatementNode>(startPos, mLexer->Position(), symbol, symbol2, right);;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseWhile()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();
    mFlowLevel++;

    auto left = ParseNamedExpr();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyElif)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'while' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();

    mFlowLevel--;

    auto next = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElse ? ParseElse() : nullptr;

    return std::make_shared<AST::WhileStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right, next);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFor()
{
    auto startPos = mLexer->Position();
    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();
    mFlowLevel++;

    auto left = ParseExprList();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyIn)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing 'in' in 'for' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseTestList();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'for' statement!"));

    auto symbol3 = mLexer->CurSymbol();
    mLexer->Advance();

    auto tc = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment ? mLexer->CurSymbol() : nullptr;
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment) mLexer->Advance();

    auto next = ParseSuite();

    mFlowLevel--;

    auto nodeElse = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElse ? ParseElse() : nullptr;

    return std::make_shared<AST::ForStatementNode>(startPos, mLexer->Position(), symbol1, left, symbol2, right, symbol3, tc, next, nodeElse);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseWith()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();
    nodes->push_back( ParseWithItem() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        nodes->push_back( ParseWithItem() );
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'with' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto tc = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment ? mLexer->CurSymbol() : nullptr;
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment) mLexer->Advance();

    auto right = ParseSuite();

    return std::make_shared<AST::WithStatementNode>(startPos, mLexer->Position(), symbol, nodes, separators, symbol2, tc, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseWithItem()
{
    auto startPos = mLexer->Position();
    auto left = ParseTest();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAs)
    {
        auto symbol = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseOrExpr();

        return std::make_shared<AST::WithItemStatementNode>(startPos, mLexer->Position(), left, symbol, right);
    }

    return std::make_shared<AST::WithItemStatementNode>(startPos, mLexer->Position(), left, nullptr, nullptr);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTry()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExcept()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExceptClause()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorated()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorators()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorator()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsyncFuncDef()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFuncDef()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseParameter()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFuncBodySuite()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTypedArgsList()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTypedAssign()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTFPDef()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseClass()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSuite()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsync()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseStmt()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSimpleStmt()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSmallStmt()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExpr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAnnAssign()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTestListStarExpr()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDel()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePass()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseBreak()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseContinue()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseReturn()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseYieldStmt()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseRaise()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImport()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportName()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportFrom()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportAsName()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedAsName()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportAsNames()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedAsNames()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedName()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGlobal()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseNonlocal()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAssert()
{
    return nullptr;
}