
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;


TEST_CASE( "Access methods", "SourceBuffer" )
{


    SECTION( "Extract char plus end of file" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+" ) );

        REQUIRE( sourceBuffer->GetChar() == L'+' );
        REQUIRE( sourceBuffer->GetChar() == 0x0000 );

    }

    SECTION( "Peek twice" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+" ) );

        REQUIRE( sourceBuffer->PeekChar() == L'+' );
        REQUIRE( sourceBuffer->GetChar() == L'+' );
        REQUIRE( sourceBuffer->GetChar() == 0x0000 );

    }

}


/* TEST_CASE( "Operators and Delimitors", "Tokenizer" )
{

    SECTION( "Operator or delimiter '+' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPlus );
    
    }

    SECTION( "Operator or delimiter '+=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+=" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPlusAssign );

    }

    SECTION( "Operator or delimiter '-' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"-" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus );

    }

    SECTION( "Operator or delimiter '-=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"-=" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinusAssign );

    }

    SECTION( "Operator or delimiter '->' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"->" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyArrow );

    }

} */
