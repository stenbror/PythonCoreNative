
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


TEST_CASE( "Operators and Delimitors", "Tokenizer" )
{

    SECTION( "Operator or delimiter '+' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPlus );
        REQUIRE( sourceBuffer->BufferPosition() == 1);
    
    }

    SECTION( "Operator or delimiter '+=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPlusAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '-' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"- " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinus );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '-=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"-= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMinusAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '->' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"-> " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyArrow );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '**=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"**= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPowerAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '**' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"** " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '*=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"*= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMulAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '*' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"* " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '//=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"//= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFloorDivAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '//' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"// " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFloorDiv );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '/=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"/= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDivAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '/' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"/ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDiv );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '<<=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"<<= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyShiftLeftAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '<<' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"<< " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyShiftLeft );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '<>' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"<> " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyNotEqual );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '<=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"<= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLessEqual );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '<' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"< " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLess );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '>>=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L">>= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyShiftRightAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '>>' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L">> " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyShiftRight );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '>=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L">= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyGreaterEqual );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '>' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"> " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyGreater );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '==' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"== " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyEqual );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '!=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"!= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyNotEqual );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '%=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"%= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyModuloAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '%' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"% " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyModulo );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '@=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"@= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMatriceAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '@' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"@ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyModulo );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '&=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"&= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitAndAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '&' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"& " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitAnd );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '|=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"|= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitOrAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '|' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"| " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitOr );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '^=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"^= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitXorAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '^' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"^ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitXor );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter ':=' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L":= " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColonAssign );
        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '...' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"... " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyElipsis );
        REQUIRE( sourceBuffer->BufferPosition() == 3);

    }

    SECTION( "Operator or delimiter '.' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L". " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyDot );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter ':' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L": " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter ';' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"; " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PySemiColon );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '~' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"~ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyBitInvert );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '(' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"( " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '[' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"[ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftBracket );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '{' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"{} " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftCurly );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '()' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"() " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftParen );

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen );

        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '[' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"[ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftBracket );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '[]' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"[] " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftBracket );

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightBracket );

        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

    SECTION( "Operator or delimiter '{' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"{} " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftCurly );
        REQUIRE( sourceBuffer->BufferPosition() == 1);

    }

    SECTION( "Operator or delimiter '{}' in Lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"{} " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyLeftCurly );

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightCurly );

        REQUIRE( sourceBuffer->BufferPosition() == 2);

    }

}


TEST_CASE( "Reserved keywords", "Tokenizer" )
{

    SECTION( "Reserved keyword '' in lexer!" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"False " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        REQUIRE( lexer->CurSymbol()->GetSymbolKind() == TokenKind::PyFalse );
        REQUIRE( sourceBuffer->BufferPosition() == 5);
    
    }

}