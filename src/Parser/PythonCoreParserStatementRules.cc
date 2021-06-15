
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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'if' statement!"));

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

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'elif' statement!"));

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

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'else' statement!"));

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

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'while' statement!"));

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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing 'in' in 'for' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseTestList();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'for' statement!"));

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

    auto symbol10 = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen ?
                        mLexer->CurSymbol() : nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen) mLexer->Advance();

    nodes->push_back( ParseWithItem() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {

        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen &&
                symbol10 != nullptr ) continue;

        nodes->push_back( ParseWithItem() );
    
    }

    if (symbol10 != nullptr && mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ')' in 'with' statement!"));

    auto symbol11 = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ?
                        mLexer->CurSymbol() :
                        nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen) mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'with' statement!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto tc = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment ? mLexer->CurSymbol() : nullptr;
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::TypeComment) mLexer->Advance();

    auto right = ParseSuite();

    return std::make_shared<AST::WithStatementNode>(startPos, mLexer->Position(), symbol, symbol10, nodes, separators, symbol11, symbol2, tc, right);
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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'try' statement!"));
    
    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = ParseSuite();  

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFinally)
    {
        auto symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'finally' statement!"));
    
        auto symbol4 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseSuite();  

        return std::make_shared<AST::TryStatementNode>(startPos, mLexer->Position(), symbol, symbol2, left, nullptr, nullptr, symbol3, symbol4, right);
    }
    else
    {
        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing 'except' in 'try' statement!"));
        auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();   

        while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyExcept) nodes->push_back( ParseExcept() );

        auto node = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElse ? ParseElse() : nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFinally)
        {
            auto symbol3 = mLexer->CurSymbol();
            mLexer->Advance();

            if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'finally' statement!"));
        
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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'except' statement!"));
    
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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name after 'as' in 'except' statement!"));
        
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

            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting 'class', 'def' or 'async' after '@'in Decorator Statement!"));
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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting ')' in decorator statement!"));

        symbol3 = mLexer->CurSymbol();
        mLexer->Advance();
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Newline)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Newline after decorator statement!"));

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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting 'def' after 'async' statement!"));

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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name of function declaration!"));

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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in function declaration!"));

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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing '(' in function declaration!"));

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen ? ParseTypedArgsList() : nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ')' in function declaration!"));

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
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Newline after TypeComment in Suite!"));

            nl = mLexer->CurSymbol();
            mLexer->Advance();

            if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Indent)
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Indent in suite!"));

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
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();
    auto tc = std::make_shared<std::vector<std::shared_ptr<Token>>>();
    std::shared_ptr<Token> div = nullptr;
    std::shared_ptr<Token> mulOp = nullptr, powerOp = nullptr;
    std::shared_ptr<AST::StatementNode> mulNode = nullptr, powerNode = nullptr;

    switch ( mLexer->CurSymbol()->GetSymbolKind() )
    {
        case TokenKind::PyMul:

            {
                mulOp = mLexer->CurSymbol();
                mLexer->Advance();

                if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                    throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '*' in argument list!"));

                mulNode = ParseTFPDef();

                while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                {
                    separators->push_back( mLexer->CurSymbol() );
                    mLexer->Advance();

                    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma )
                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument list!"));

                    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon ) continue;

                    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower )
                    {
                        powerOp = mLexer->CurSymbol();
                        mLexer->Advance();

                        if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '**' in argument list!"));

                        powerNode = ParseTFPDef();

                        if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                        {
                            separators->push_back( mLexer->CurSymbol() );
                            mLexer->Advance();
                        }

                        if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
       
                        continue;
                    }

                    nodes->push_back( ParseTFPDef() );
                }
            }
            break;

        case TokenKind::PyPower:
            
            {
                powerOp = mLexer->CurSymbol();
                mLexer->Advance();

                if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                    throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '**' in argument list!"));

                powerNode = ParseTFPDef();

                if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                {
                    separators->push_back( mLexer->CurSymbol() );
                    mLexer->Advance();
                }

                if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                    throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
            }
            break;

        default:
            {
                nodes->push_back( ParseTFPDef() );

                while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                {
                    separators->push_back( mLexer->CurSymbol() );
                    mLexer->Advance();

                    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
 
                    if (    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul ||
                            mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower ||
                            mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon ||
                            mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDiv) continue;

                    nodes->push_back( ParseTFPDef() );
                }

                if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDiv )
                {
                    div = mLexer->CurSymbol();
                    mLexer->Advance();

                    auto lastToken = div;

                    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon )
                    {
                        while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                        {
                            separators->push_back( mLexer->CurSymbol() );
                            lastToken = mLexer->CurSymbol();
                            mLexer->Advance();

                            if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
                             
                            if (    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul ||
                                    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower ||
                                    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon) continue;

                            nodes->push_back( ParseTFPDef() );

                            if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma)
                                return std::make_shared<AST::TypedArgsListStatementNode>(startPos, mLexer->Position(), nodes, separators, div, mulOp, mulNode, powerOp, powerNode, tc);
                        }

                        if (lastToken->GetSymbolKind() != TokenKind::PyComma)
                            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting ',' after '/' in argument list!"));

                        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul)
                        {
                            mulOp = mLexer->CurSymbol();
                            mLexer->Advance();

                            if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '*' in argument list!"));

                            mulNode = ParseTFPDef();

                            while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                            {
                                separators->push_back( mLexer->CurSymbol() );
                                mLexer->Advance();

                                if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma )
                                    throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument list!"));

                                if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon ) continue;

                                if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower )
                                {
                                    powerOp = mLexer->CurSymbol();
                                    mLexer->Advance();

                                    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '**' in argument list!"));

                                    powerNode = ParseTFPDef();

                                    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                                    {
                                        separators->push_back( mLexer->CurSymbol() );
                                        mLexer->Advance();
                                    }

                                    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
                
                                    continue;
                                }

                                nodes->push_back( ParseTFPDef() );
                            }
                        }
                        else if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower)
                        {
                            powerOp = mLexer->CurSymbol();
                            mLexer->Advance();

                            if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
                                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name literal after '**' in argument list!"));

                            powerNode = ParseTFPDef();

                            if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                            {
                                separators->push_back( mLexer->CurSymbol() );
                                mLexer->Advance();
                            }

                            if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
                                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Unexpected ',' in argument!"));
                        }
                    }
                }
            }
            break;
    }

    return std::make_shared<AST::TypedArgsListStatementNode>(startPos, mLexer->Position(), nodes, separators, div, mulOp, mulNode, powerOp, powerNode, tc);
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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name in argument!"));

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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Name in 'class' declaration!"));

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
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ')' in 'class' declaration!"));
    
        symbol4 = mLexer->CurSymbol();
        mLexer->Advance();
    }

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing ':' in 'class' declaration!"));


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
                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Missing Indent in suite!"));

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

            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting 'with', 'def' or 'for' after 'async'!"));
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

        case TokenKind::Name:
            
            {
                auto match = std::static_pointer_cast<NameToken>(mLexer->CurSymbol());

                return match->IsMatchSoftKeyword() ? ParseMatch() : ParseSimpleStmt();
            }
        
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
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Newline after simple statement list!"));

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
            case TokenKind::PyRightParen:
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

    if (mFlowLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Found 'break' outside of a loop statement!"));

    return std::make_shared<AST::BreakStatementNode>(startPos, mLexer->Position(), symbol);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseContinue()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mFlowLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Found 'continue' outside of a loop statement!"));

    return std::make_shared<AST::ContinueStatementNode>(startPos, mLexer->Position(), symbol);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseReturn()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mFuncLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Found 'return' outside of a func declaration!"));

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::Newline:
        case TokenKind::PySemiColon:

            return std::make_shared<AST::ReturnStatementNode>(startPos, mLexer->Position(), symbol, nullptr);

        default:

            auto right = ParseTestListStarExpr();

            return std::make_shared<AST::ReturnStatementNode>(startPos, mLexer->Position(), symbol, right);
            
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseYieldStmt()
{
    auto startPos = mLexer->Position();

    if (mFuncLevel == 0) throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Found 'yield' outside of a func declaration!"));

    auto right = ParseYieldExpr();

    return std::make_shared<AST::YieldStatementNode>(startPos, mLexer->Position(), right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseRaise()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::Newline:
        case TokenKind::PySemiColon:

            return std::make_shared<AST::RaiseStatementNode>(startPos, mLexer->Position(), symbol, nullptr, nullptr, nullptr);

        default:
            
            auto left = ParseTest();

            if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFrom)
            {
                auto symbol2 = mLexer->CurSymbol();
                mLexer->Advance();

                auto right = ParseTest();

                return std::make_shared<AST::RaiseStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right);
            }

            return std::make_shared<AST::RaiseStatementNode>(startPos, mLexer->Position(), symbol, left, nullptr, nullptr);
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImport()
{
    return mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyImport ? ParseImportName() : ParseImportFrom();
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportName()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseDottedName();

    return std::make_shared<AST::ImportStatementNode>(startPos, mLexer->Position(), symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportFrom()
{
    auto startPos = mLexer->Position();
    auto symbol1 = mLexer->CurSymbol(); // 'from'
    mLexer->Advance();
    auto dots = std::shared_ptr<std::vector<std::shared_ptr<Token>>>();
    std::shared_ptr<AST::StatementNode> left = nullptr, right = nullptr;

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDot ||
            mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElipsis)
            {
                dots->push_back( mLexer->CurSymbol() );
                mLexer->Advance();
            }

    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyImport && dots->size() == 0 )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting 'from' part in import statement!"));
    
    else if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyImport )
        left = ParseDottedName(); 

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyImport )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting 'import' in from statement!"));

    auto symbol2 = mLexer->CurSymbol(); // 'import'
    mLexer->Advance();

    switch ( mLexer->CurSymbol()->GetSymbolKind() )
    {
        case TokenKind::PyMul:
            
            {
                auto symbol5 = mLexer->CurSymbol();
                mLexer->Advance();

                return std::make_shared<AST::ImportFromStatementNode>(startPos, mLexer->Position(), symbol1, dots, left, symbol2, symbol5, nullptr, nullptr);
            }

        case TokenKind::PyLeftParen:

            {
                auto symbol3 = mLexer->CurSymbol(); // '(')
                mLexer->Advance();

                right = ParseImportAsNames();

                if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen )
                    throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting ')' in 'from' statement!"));

                auto symbol4 = mLexer->CurSymbol(); // ')'
                mLexer->Advance();

                return std::make_shared<AST::ImportFromStatementNode>(startPos, mLexer->Position(), symbol1, dots, left, symbol2, symbol3, right, symbol4);
            }

        default:

            right = ParseImportAsNames();

            return std::make_shared<AST::ImportFromStatementNode>(startPos, mLexer->Position(), symbol1, dots, left, symbol2, nullptr, right, nullptr);
    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportAsName()
{
    auto startPos = mLexer->Position();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name in import argument!"));

    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();

    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAs )
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name in import argument!"));

        auto symbol3 = mLexer->CurSymbol();
        mLexer->Advance();

        return std::make_shared<AST::ImportAsNameStatementNode>(startPos, mLexer->Position(), symbol1, symbol2, symbol3);
    }

    return std::make_shared<AST::ImportAsNameStatementNode>(startPos, mLexer->Position(), symbol1, nullptr, nullptr);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedAsName()
{
    auto startPos = mLexer->Position();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name in import argument!"));

    auto left = ParseDottedName();

    if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAs )
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name in import argument!"));

        auto symbol3 = std::static_pointer_cast<NameToken>( mLexer->CurSymbol() );
        mLexer->Advance();

        return std::make_shared<AST::DottedAsNameStatementNode>(startPos, mLexer->Position(), left, symbol2, symbol3);
    }

    return left;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseImportAsNames()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseImportAsName() );

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ||
                mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline ||
                mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PySemiColon )
                    continue;

        nodes->push_back( ParseImportAsName() );
    }

    if ( nodes->size() == 1 && separators->size() == 0 ) return nodes->back();

    return std::make_shared<AST::ImportAsNamesStatementNode>(startPos, mLexer->Position(), nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedAsNames()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseDottedAsName() );

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        nodes->push_back( ParseDottedAsName() );
    }

    if ( nodes->size() == 1 && separators->size() == 0 ) return nodes->back();

    return std::make_shared<AST::DottedAsNamesStatementNode>(startPos, mLexer->Position(), nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseDottedName()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<NameToken>>>();
    auto dots = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting atleast one Name literal in dotted argument!"));

    nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
    mLexer->Advance();

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDot )
    {
        dots->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expecting Name literal after '.' in dotted argument!"));

        nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
        mLexer->Advance();
    }

    return std::make_shared<AST::DottedNameStatementNode>(startPos, mLexer->Position(), nodes, dots);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGlobal()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<NameToken>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expect atleast one Name in 'global' statement!"));

    nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
    mLexer->Advance();

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expect Name after ',' in 'global' statement!"));

        nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
        mLexer->Advance();
    }

    return std::make_shared<AST::GlobalStatementNode>(startPos, mLexer->Position(), symbol, nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseNonlocal()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<NameToken>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expect atleast one Name in 'nonlocal' statement!"));

    nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
    mLexer->Advance();

    while ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma )
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::wstring>(L"Expect Name after ',' in 'nonlocal' statement!"));

        nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
        mLexer->Advance();
    }

    return std::make_shared<AST::NonlocalStatementNode>(startPos, mLexer->Position(), symbol, nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAssert()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = ParseTest();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {
        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = ParseTest();

        return std::make_shared<AST::AssertStatementNode>(startPos, mLexer->Position(), symbol, left, symbol2, right);
    }

    return std::make_shared<AST::AssertStatementNode>(startPos, mLexer->Position(), symbol, left, nullptr, nullptr);
}
