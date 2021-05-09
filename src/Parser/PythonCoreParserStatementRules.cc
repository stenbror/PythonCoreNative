
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
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'try' statement!"));
    
    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = ParseSuite();  

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFinally)
    {
        auto symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'finally' statement!"));
    
        auto symbol4 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseSuite();  

        return std::make_shared<AST::TryStatementNode>(startPos, mLexer->Position(), symbol, symbol2, left, nullptr, nullptr, symbol3, symbol4, right);
    }
    else
    {
        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing 'except' in 'try' statement!"));
        auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();   

        while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyExcept) nodes->push_back( ParseExcept() );

        auto node = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElse ? ParseElse() : nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFinally)
        {
            auto symbol3 = mLexer->CurSymbol();
            mLexer->Advance();

            if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'finally' statement!"));
        
            auto symbol4 = mLexer->CurSymbol();
            mLexer->Advance();

            auto right = ParseSuite();

            return std::make_shared<AST::TryStatementNode>(startPos, mLexer->Position(), symbol, symbol2, left, nodes, node, symbol3, symbol4, right);
        }

        return std::make_shared<AST::TryStatementNode>(startPos, mLexer->Position(), symbol, symbol2, left, nodes, node, nullptr, nullptr, nullptr);
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExcept()
{
    auto startPos = mLexer->Position();
    auto left = ParseExceptClause();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'except' statement!"));
    
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();  

    return std::make_shared<AST::ExceptNode>(startPos, mLexer->Position(), left, symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExceptClause()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon)
    {
        return std::make_shared<AST::ExceptClauseNode>(startPos, mLexer->Position(), symbol, nullptr, nullptr, nullptr);
    }

    auto left = ParseTest();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAs)
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Name after 'as' in 'except' statement!"));
        
        auto right = std::static_pointer_cast<NameToken> ( mLexer->CurSymbol() );
        mLexer->Advance();

        return std::make_shared<AST::ExceptClauseNode>(startPos, mLexer->Position(), symbol, left, symbol2, right);
    }

    return std::make_shared<AST::ExceptClauseNode>(startPos, mLexer->Position(), symbol, left, nullptr, nullptr);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorated()
{
    auto startPos = mLexer->Position();
    auto left = ParseDecorators();

    std::shared_ptr<AST::StatementNode> right = nullptr;

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyClass:
            right = ParseClass();
            break;
        case TokenKind::PyDef:
            right = ParseFuncDef();
            break;
        case TokenKind::PyAsync:
            right = ParseAsyncFuncDef();
            break;
        default:
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting 'class', 'def' or 'async' after '@'in Decorator Statement!"));
    }

    return std::make_shared<AST::DecoratedStatementNode>(startPos, mLexer->Position(), left, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorators()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMatrice) nodes->push_back( ParseDecorator() );

    return std::make_shared<AST::DecoratorsStatementNode>(startPos, mLexer->Position(), nodes);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDecorator()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = ParseDottedName();

    std::shared_ptr<Token> symbol2 = nullptr, symbol3 = nullptr, symbol4 = nullptr;
    std::shared_ptr<AST::ExpressionNode> right = nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen)
    {
        symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        right = mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen ? ParseArgList() : nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting ')' in decorator statement!"));

        symbol3 = mLexer->CurSymbol();
        mLexer->Advance();
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting Newline after decorator statement!"));

    symbol4 = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::DecoratorStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right, symbol3, symbol4);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsyncFuncDef()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyDef)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting 'def' after 'async' statement!"));

    auto right = ParseFuncDef();

    return std::make_shared<AST::AsyncStatementNode>(startPos, mLexer->Position(), symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFuncDef()
{
    auto startPos = mLexer->Position();
    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();
    mFuncLevel++;
    
    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting Name of function declaration!"));

    auto symbol2 = std::static_pointer_cast<NameToken>(mLexer->CurSymbol());
    mLexer->Advance();

    auto left = ParseParameter();

    std::shared_ptr<Token> symbol3 = nullptr;
    std::shared_ptr<AST::ExpressionNode> right = nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyArrow)
    {
        symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        right = ParseTest();
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in function declaration!"));

    auto symbol4 = mLexer->CurSymbol();
    mLexer->Advance();

    auto tc = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment ? mLexer->CurSymbol() : nullptr;
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment) mLexer->Advance();

    auto next = ParseFuncBodySuite();

    mFuncLevel--;

    return std::make_shared<AST::FuncDefStatementNode>(startPos, mLexer->Position(), symbol1, symbol2, left, symbol3, right, symbol4, tc, next);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseParameter()
{
    auto startPos = mLexer->Position();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing '(' in function declaration!"));

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen ? ParseTypedArgsList() : nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ')' in function declaration!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::ParameterStatementNode>(startPos, mLexer->Position(), symbol, right, symbol2);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFuncBodySuite()
{
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
    {
        auto startPos = mLexer->Position();
        auto symbol1 = mLexer->CurSymbol();
        mLexer->Advance();

        std::shared_ptr<Token> tc = nullptr, nl = nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment)
        {
            tc = mLexer->CurSymbol();
            mLexer->Advance();

            if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Newline after TypeComment in Suite!"));

            nl = mLexer->CurSymbol();
            mLexer->Advance();

            if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Indent)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Indent in suite!"));

            auto symbol2 = mLexer->CurSymbol();
            mLexer->Advance();

            auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
            nodes->push_back( ParseStmt() );
            auto newlines = std::make_shared<std::vector<std::shared_ptr<Token>>>();

            while (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Dedent)
            {
                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
                {
                    newlines->push_back(mLexer->CurSymbol());
                    mLexer->Advance();
                }
                else
                {
                    nodes->push_back( ParseStmt() );
                }
            }

            auto symbol3 = mLexer->CurSymbol();
            mLexer->Advance();

            return std::make_shared<AST::FuncBodySuiteStatementNode>(startPos, mLexer->Position(), symbol1, tc, nl, symbol2,  nodes, newlines, symbol3);
        }
    }

    return ParseSimpleStmt();
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTypedArgsList()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTypedAssign()
{
    auto startPos = mLexer->Position();
    auto left =ParseTFPDef();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAssign)
    {
        auto symbol = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseTest();

        return std::make_shared<AST::TFPDefAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);
    }

    return left;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTFPDef()
{
    auto startPos = mLexer->Position();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Name in argument!"));

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon)
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseTest();

        return std::make_shared<AST::TFPDefStatementNode>(startPos, mLexer->Position(), symbol, symbol2, right);
    }

    return std::make_shared<AST::TFPDefStatementNode>(startPos, mLexer->Position(), symbol, nullptr, nullptr);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseClass()
{
    auto startPos = mLexer->Position();
    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Name in 'class' declaration!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    std::shared_ptr<Token> symbol3 = nullptr, symbol4 = nullptr;
    std::shared_ptr<AST::ExpressionNode> left = nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen)
    {
        symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        left = mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen ? ParseArgList() : nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ')' in 'class' declaration!"));
    
        symbol4 = mLexer->CurSymbol();
        mLexer->Advance();
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing ':' in 'class' declaration!"));


    auto symbol5 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseSuite();

    return std::make_shared<AST::ClassStatementNode>(startPos, mLexer->Position(), symbol1, symbol2, symbol3, left, symbol4, symbol5, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSuite()
{
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
    {
        auto startPos = mLexer->Position();
        auto symbol1 = mLexer->CurSymbol();
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Indent)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Missing Indent in suite!"));

        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
        nodes->push_back( ParseStmt() );
        auto newlines = std::make_shared<std::vector<std::shared_ptr<Token>>>();

        while (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Dedent)
        {
            if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
            {
                newlines->push_back(mLexer->CurSymbol());
                mLexer->Advance();
            }
            else
            {
                nodes->push_back( ParseStmt() );
            }
        }

        auto symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        return std::make_shared<AST::SuiteStatementNode>(startPos, mLexer->Position(), symbol1, symbol2, nodes, newlines, symbol3);
    }

    return ParseSimpleStmt();
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsync()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    std::shared_ptr<AST::StatementNode> right = nullptr;

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyWith:
            right = ParseWith();
            break;
        case TokenKind::PyDef:
            right = ParseFuncDef();
            break;
        case TokenKind::PyFor:
            right = ParseFor();
            break;
        default:
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting 'with', 'def' or 'for' after 'async'!"));
    }

    return std::make_shared<AST::AsyncStatementNode>(startPos, mLexer->Position(), symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseStmt()
{
    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyIf:
        case TokenKind::PyFor:
        case TokenKind::PyWhile:
        case TokenKind::PyWith:
        case TokenKind::PyTry:
        case TokenKind::PyDef:
        case TokenKind::PyClass:
        case TokenKind::PyAsync:
        case TokenKind::PyMatrice:
            return ParseCompound();
        default:
            return ParseSimpleStmt();
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSimpleStmt()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseSmallStmt() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PySemiColon)
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline) nodes->push_back( ParseSmallStmt() );
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting Newline after simple statement list!"));

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::SimpleStatementNode>(startPos, mLexer->Position(), nodes, separators, symbol);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSmallStmt()
{
    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyDel:
            return ParseDel();
        case TokenKind::PyPass:
            return ParsePass();
        case TokenKind::PyBreak:
            return ParseBreak();
        case TokenKind::PyContinue:
            return ParseContinue();
        case TokenKind::PyRaise:
            return ParseRaise();
        case TokenKind::PyYield:
            return ParseYieldStmt();
        case TokenKind::PyReturn:
            return ParseReturn();
        case TokenKind::PyImport:
        case TokenKind::PyFrom:
            return ParseImport();
        case TokenKind::PyGlobal:
            return ParseGlobal();
        case TokenKind::PyNonLocal:
            return ParseNonlocal();
        case TokenKind::PyAssert:
            return ParseAssert();
        default:
            return ParseExpr();
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseExpr()
{
    auto startPos = mLexer->Position();
    std::shared_ptr<Token> symbol = nullptr;
    std::shared_ptr<AST::ExpressionNode> right = nullptr;
    auto left = ParseTestListStarExpr();

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyPlusAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::PlusAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyMinusAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::MinusAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyMulAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::MulAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyDivAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::DivAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyPowerAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::PowerAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyFloorDivAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::FloorDivAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyShiftLeftAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::ShiftLeftAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyShiftRightAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::ShiftRightAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyModuloAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::ModuloAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyMatriceAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::MatriceAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyBitAndAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::BitAndAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyBitXorAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::BitXorAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyBitOrAssign:

            symbol = mLexer->CurSymbol();
            mLexer->Advance();
            right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? ParseYieldExpr() : ParseTestList();

            return std::make_shared<AST::BitOrAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right);

        case TokenKind::PyColon:

            return ParseAnnAssign(startPos, left);

        case TokenKind::PyAssign:
            
            {
                auto operators = std::make_shared<std::vector<std::shared_ptr<Token>>>();
                auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::Node>>>();

                while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAssign)
                {
                    operators->push_back( mLexer->CurSymbol() );
                    mLexer->Advance();

                    nodes->push_back( 
                        mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? 
                            std::static_pointer_cast<AST::Node>( ParseYieldExpr() ) :
                            std::static_pointer_cast<AST::Node>( ParseTestListStarExpr() ) 
                    );
                }

                auto tc = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment ? mLexer->CurSymbol() : nullptr;
                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment) mLexer->Advance();

                return std::make_shared<AST::AssignStatementNode>(startPos, mLexer->Position(), left, operators, nodes, tc);
            }

        default:
            return left;
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAnnAssign(unsigned int startPos, std::shared_ptr<AST::StatementNode> left)
{
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseTest();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAssign)
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        auto next = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyYield ? 
                            std::static_pointer_cast<AST::Node>( ParseYieldExpr() ) :
                            std::static_pointer_cast<AST::Node>( ParseTestListStarExpr() );

        return std::make_shared<AST::AnnAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right, symbol2, next);
    }

    return std::make_shared<AST::AnnAssignStatementNode>(startPos, mLexer->Position(), left, symbol, right, nullptr, nullptr);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseTestListStarExpr()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::ExpressionNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul ? ParseStarExpr() : ParseTest() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        switch (mLexer->CurSymbol()->GetSymbolKind())
        {
            case TokenKind::PyPlusAssign:
            case TokenKind::PyMinusAssign:
            case TokenKind::PyMulAssign:
            case TokenKind::PyDivAssign:
            case TokenKind::PyModuloAssign:
            case TokenKind::PyMatriceAssign:
            case TokenKind::PyPowerAssign:
            case TokenKind::PyFloorDivAssign:
            case TokenKind::PyShiftLeftAssign:
            case TokenKind::PyShiftRightAssign:
            case TokenKind::PyBitAndAssign:
            case TokenKind::PyBitXorAssign:
            case TokenKind::PyBitOrAssign:
            case TokenKind::PyAssign:
            case TokenKind::PyColon:
            case TokenKind::PySemiColon:
            case TokenKind::Newline:
                break;
            default:
                nodes->push_back( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul ? ParseStarExpr() : ParseTest() );
        }
    }

    return std::make_shared<AST::TestListStarExprListStatementNode>(startPos, mLexer->Position(), nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDel()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseExprList();

    return std::make_shared<AST::DelStatementNode>(startPos, mLexer->Position(), symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePass()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::PassStatementNode>(startPos, mLexer->Position(), symbol);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseBreak()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mFlowLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Found 'break' outside of a loop statement!"));

    return std::make_shared<AST::BreakStatementNode>(startPos, mLexer->Position(), symbol);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseContinue()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mFlowLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Found 'continue' outside of a loop statement!"));

    return std::make_shared<AST::ContinueStatementNode>(startPos, mLexer->Position(), symbol);
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