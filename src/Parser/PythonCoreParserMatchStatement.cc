
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
    auto startPos = mLexer->Position();
    auto right = ParseStarNamedExpression();

    return std::make_shared<AST::SubjectExprNode>(startPos, mLexer->Position(), right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseCaseBlock()
{
    auto startPos = mLexer->Position();

    if (    mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name && 
            std::static_pointer_cast<NameToken> (mLexer->CurSymbol())->IsCaseSoftKeyword() )
            {

                auto symbol = mLexer->CurSymbol();
                mLexer->Advance();

                auto left = ParsePatterns();

                auto right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyIf ?
                                ParseGuard() : nullptr;

                if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyColon)
                    throw std::make_shared<SyntaxError>(
                                mLexer->Position(), 
                                mLexer->CurSymbol(),
                                std::make_shared<std::wstring>(L"Expecting ':' in 'case' statement!"));

                auto symbol2 = mLexer->CurSymbol();
                mLexer->Advance();

                auto next = ParseSuite();

                return std::make_shared<AST::CaseStatementNode>(
                        startPos,
                        mLexer->Position(),
                        std::static_pointer_cast<NameToken>(symbol), 
                        left, 
                        right, 
                        symbol2, 
                        next);

            }

    else
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting 'case' in 'match' statement!"));

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGuard()
{
    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();  /* 'if' */
    mLexer->Advance();

    auto right = ParseNamedExpr();

    return std::make_shared<AST::GuardNode>(startPos, mLexer->Position(), symbol, right);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePatterns()
{

    return mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitOr ? 
        ParsePattern() :
        ParseOpenSequencePattern(); 

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParsePattern()
{

    auto startPos = mLexer->Position();
    auto left = ParseOrPattern();

    return mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAs ?
        ParseAsPattern(startPos, left) :
        left;

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseAsPattern(unsigned int startPos, std::shared_ptr<AST::StatementNode> left)
{

    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseCapturePattern();

    return std::make_shared<AST::AsPatternNode>(
        startPos,
        mLexer->Position(),
        left,
        symbol, /* 'as' */
        right );

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseOrPattern()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    separators->push_back( mLexer->CurSymbol() );
    mLexer->Advance();
    nodes->push_back( ParseClosedPattern() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitOr)
    {

        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();
        nodes->push_back( ParseClosedPattern() );
    
    }

    return std::make_shared<AST::OrPatternNode>(
        startPos,
        mLexer->Position(),
        nodes,
        separators );
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseClosedPattern()
{

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyMinus:
        case TokenKind::Number:
        case TokenKind::String:
        case TokenKind::PyNone:
        case TokenKind::PyTrue:
        case TokenKind::PyFalse:

            return ParseLiteralPattern();

        case TokenKind::PyLeftBracket:

            return ParseSequencePattern();

        case TokenKind::PyLeftParen:
            {

                auto startPos = mLexer->CurSymbol()->GetTokenStartPosition(); /* Start of first token */
                auto symbol = mLexer->CurSymbol();
                mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitOr)
                {

                    mLexer->UnWindTokenStream(startPos); /* Reset back Token stream */

                    return ParseGroupPattern();
                
                }

                mLexer->UnWindTokenStream(startPos); /* Reset back Token stream */

                return ParseSequencePattern();

            }
            

        case TokenKind::PyLeftCurly:

            return ParseMappingPattern();

        case TokenKind::Name:
            {
                auto symbol = std::static_pointer_cast<NameToken>( mLexer->CurSymbol() );
                auto startPos = mLexer->CurSymbol()->GetTokenStartPosition();

                if (symbol->IsWildCardPattern() ) return ParseWildCardPattern();

                else  
                {

                    mLexer->Advance();

                    if (    mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyDot &&
                            mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyLeftParen &&
                            mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyAssign )
                            {

                                mLexer->UnWindTokenStream(startPos); /* Reset back Token stream */

                                return ParseCapturePattern();

                            }

                    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDot)
                    {

                        mLexer->Advance();

                        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name) mLexer->Advance();
                        else 
                            throw std::make_shared<SyntaxError>(
                                        mLexer->Position(), 
                                        mLexer->CurSymbol(),
                                        std::make_shared<std::wstring>(L"Expecting Name after '.' in pattern!"));

                    }

                    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen)
                    {

                        mLexer->UnWindTokenStream(startPos); /* Reset back Token stream */

                        return ParseClassPattern();
                    
                    }

                    mLexer->UnWindTokenStream(startPos); /* Reset back Token stream */

                    return ParseValuePattern();
                    
                }

            }

        default:

            throw std::make_shared<SyntaxError>(
                        mLexer->Position(), 
                        mLexer->CurSymbol(),
                        std::make_shared<std::wstring>(L"Expecting a valid pattern!"));


    }
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseLiteralPattern()
{

    auto startPos = mLexer->Position();

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyNone:
        case TokenKind::PyTrue:
        case TokenKind::PyFalse:
        case TokenKind::String:
            {
                
                auto symbol = mLexer->CurSymbol();
                mLexer->Advance();

                return std::make_shared<AST::LiteralPatternNode>(
                    startPos,
                    mLexer->Position(),
                    symbol,
                    nullptr );

            }
        default:    /* signed_number | complex_number */
            {
                auto symbol = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus ?
                    mLexer->CurSymbol() : nullptr;

                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus) mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind:: Number)
                    throw std::make_shared<SyntaxError>(
                            mLexer->Position(), 
                            mLexer->CurSymbol(),
                            std::make_shared<std::wstring>(L"Expecting Number after '-' in signed number!"));

                auto left = std::static_pointer_cast<NumberToken>(mLexer->CurSymbol());

                auto node = left->IsRealNumber() ? 
                    ParseComplexNumber(startPos, symbol, left) :
                    ParseSignedNumber(startPos, symbol, left);

                return std::make_shared<AST::LiteralPatternNode>(
                    startPos,
                    mLexer->Position(),
                    nullptr,
                    node );
                
            }
            
    }

    return nullptr; /* Should never happend. */

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseLiteralExpr()
{
    
    auto startPos = mLexer->Position();

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyNone:
        case TokenKind::PyTrue:
        case TokenKind::PyFalse:
        case TokenKind::String:
            {
                
                auto symbol = mLexer->CurSymbol();
                mLexer->Advance();

                return std::make_shared<AST::LiteralPatternNode>(
                    startPos,
                    mLexer->Position(),
                    symbol,
                    nullptr );

            }
        default:    /* signed_number | complex_number */
            {
                auto symbol = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus ?
                    mLexer->CurSymbol() : nullptr;

                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus) mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind:: Number)
                    throw std::make_shared<SyntaxError>(
                            mLexer->Position(), 
                            mLexer->CurSymbol(),
                            std::make_shared<std::wstring>(L"Expecting Number after '-' in signed number!"));

                auto left = std::static_pointer_cast<NumberToken>(mLexer->CurSymbol());

                auto node = left->IsRealNumber() ? 
                    ParseComplexNumber(startPos, symbol, left) :
                    ParseSignedNumber(startPos, symbol, left);

                return std::make_shared<AST::LiteralExprNode>(
                    startPos,
                    mLexer->Position(),
                    nullptr,
                    node );
            }
    } 
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseComplexNumber( unsigned int startPos, std::shared_ptr<Token> symbol, std::shared_ptr<NumberToken> left )
{

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyPlus:
        case TokenKind::PyMinus:
            {

                auto symbol2 = mLexer->CurSymbol();
                mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Number)
                {

                    auto right = std::static_pointer_cast<NumberToken>(mLexer->CurSymbol());

                    if (right->IsImaginaryNumber())
                    {

                        mLexer->Advance();

                        return std::make_shared<AST::ComplexNumberNode>(
                            startPos,
                            mLexer->Position(),
                            symbol,
                            left,
                            symbol2,
                            right );

                    }

                    throw std::make_shared<SyntaxError>(
                        mLexer->Position(), 
                        mLexer->CurSymbol(),
                        std::make_shared<std::wstring>(L"Expecting imaginary number part of complex number!"));

                }

                throw std::make_shared<SyntaxError>(
                        mLexer->Position(), 
                        mLexer->CurSymbol(),
                        std::make_shared<std::wstring>(L"Expecting imaginary number after '+' or '-' in part of complex number!"));

            }

            break;

        default:

            throw std::make_shared<SyntaxError>(
                        mLexer->Position(), 
                        mLexer->CurSymbol(),
                        std::make_shared<std::wstring>(L"Expecting imaginary number and '+' or '-' in part of complex number!"));

    }

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSignedNumber( unsigned int startPos, std::shared_ptr<Token> symbol, std::shared_ptr<NumberToken> left )
{

    return std::make_shared<AST::SignedNumberNode>(startPos, mLexer->Position(), symbol, left);

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseCapturePattern()
{
    auto startPos = mLexer->Position();
    auto symbol = std::static_pointer_cast<NameToken>( mLexer->CurSymbol() );
    mLexer->Advance();

    return std::make_shared<AST::CapturePatternNode>(
        startPos,
        mLexer->Position(),
        symbol );

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseWildCardPattern()
{
    auto startPos = mLexer->Position();

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name && std::static_pointer_cast<NameToken>(mLexer->CurSymbol())->IsWildCardPattern() )
    {

        auto symbol = mLexer->CurSymbol();  /* '_' */
        mLexer->Advance();

        return std::make_shared<AST::WildCardPatternNode>(startPos, mLexer->Position(), symbol);

    }

    return nullptr; /* Should never happend, because we need '_' to get to this rule. */
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseValuePattern()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<NameToken>>>();
    auto dots = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
    mLexer->Advance();

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDot)
    {

        dots->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
            throw ;

        nodes->push_back( std::static_pointer_cast<NameToken>(mLexer->CurSymbol()) );
        mLexer->Advance();

    }

    /* We alredy made sure we dont have more '.', '(' or '=' */

    return std::make_shared<AST::ValuePatternNode>(
                        startPos,
                        mLexer->Position(),
                        nodes,
                        dots );

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseGroupPattern()
{
    auto startPos = mLexer->Position();
    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParsePattern();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting ')' in pattern!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    return std::make_shared<AST::GroupPatternNode>(
        startPos,
        mLexer->Position(),
        symbol1,
        right,
        symbol2 );
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSequencePattern()
{

    auto startPos = mLexer->Position();
    
    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftBracket)
    {

        auto symbol1 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightBracket ?
                        ParseMaybeeSequencePattern() :
                        nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightBracket)
            throw ;

        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        return std::make_shared<AST::SequencePatternNode>(
                    startPos,
                    mLexer->Position(),
                    symbol1,
                    right,
                    symbol2 );

    }
    else
    {

        auto symbol1 = mLexer->CurSymbol();
        mLexer->Advance();

        auto right = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ?
                        ParseOpenSequencePattern() : // Check for single entry. Group Pattern if onlye one.
                        nullptr;

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
            throw ;

        auto symbol2 = mLexer->CurSymbol();
        mLexer->Advance();

        if (right != nullptr && std::static_pointer_cast<AST::OpenSequencePatternNode>(right)->IsGroupPattern() )
        {

            return std::make_shared<AST::GroupPatternNode>(
                    startPos,
                    mLexer->Position(),
                    symbol1,
                    right,
                    symbol2 );

        }

        return std::make_shared<AST::SequencePatternNode>(
                    startPos,
                    mLexer->Position(),
                    symbol1,
                    right,
                    symbol2 );

    }
    
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseOpenSequencePattern()
{
    auto startPos = mLexer->Position();
    mLexer->Advance();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseMaybeeStarExpr() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {

        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ) continue;

        nodes->push_back( ParseMaybeeStarExpr() );
    
    }

    return std::make_shared<AST::OpenSequencePatternNode>(
                        startPos,
                        mLexer->Position(),
                        nodes,
                        separators );

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMaybeeSequencePattern()
{
    
    auto startPos = mLexer->Position();
    mLexer->Advance();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseMaybeeStarExpr() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {

        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightBracket ) continue;

        nodes->push_back( ParseMaybeeStarExpr() );
    
    }

    return std::make_shared<AST::MaybeeStarSequencePatternNode>(
                        startPos,
                        mLexer->Position(),
                        nodes,
                        separators );

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseMaybeeStarExpr()
{
    return mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul ?
                ParseStarPattern() :
                ParsePattern();

}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseStarPattern()
{

    auto startPos = mLexer->Position();
    auto symbol = mLexer->CurSymbol();
    mLexer->Advance();

    std::shared_ptr<AST::StatementNode> right = nullptr;

    if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Name)
    {

        auto a = std::static_pointer_cast<NameToken>( mLexer->CurSymbol() );

        if (a->IsNotWildCardPrefixed()) right = ParseWildCardPattern();

        else
            throw std::make_shared<SyntaxError>(
                        mLexer->Position(), 
                        mLexer->CurSymbol(),
                        std::make_shared<std::wstring>(L"Expecting '*' '_' pattern!"));

    }
    else
    {

        right = ParseCapturePattern();
    
    }

    return std::make_shared<AST::StarPatternNode>(startPos, mLexer->Position(), symbol, right);

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
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParsePattern() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
            nodes->push_back( ParsePattern() );
    }

    return std::make_shared<AST::PositionalPatternsNode>(startPos, mLexer->Position(), nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseKeywordPatterns()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    nodes->push_back( ParseKeywordPattern() );

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
    {
        separators->push_back( mLexer->CurSymbol() );
        mLexer->Advance();

        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen)
            nodes->push_back( ParseKeywordPattern() );
    }

    return std::make_shared<AST::KeywordPatternsNode>(startPos, mLexer->Position(), nodes, separators);
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseKeywordPattern()
{
    auto startPos = mLexer->Position();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::Name)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting Name in keyword pattern!"));

    auto symbol = std::static_pointer_cast<NameToken>( mLexer->CurSymbol() );
    mLexer->Advance();

    if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyAssign)
        throw std::make_shared<SyntaxError>(
            mLexer->Position(), 
            mLexer->CurSymbol(),
            std::make_shared<std::wstring>(L"Expecting '=' in keyword pattern!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParsePattern();

    return std::make_shared<AST::KeywordPatternNode>(
                            startPos, mLexer->Position(), symbol, symbol2, right);
}
