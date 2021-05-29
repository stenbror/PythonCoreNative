
#include <catch2/catch.hpp>

#include <PythonCoreParser.h>


using namespace PythonCoreNative::RunTime::Parser;

TEST_CASE( "Rule: Atom", "Parser - Expression rules" )
{

    SECTION( "Atom 'False'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"False " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomFalseNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyFalse );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 5 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "Atom 'None'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"None " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomNoneNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyNone );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 5 ) ; 

    }

    SECTION( "Atom 'True'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"True " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomTrueNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyTrue );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 5 ) ; 

    }

    SECTION( "Atom '...'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"... " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomElipsisNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyElipsis );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 4 ) ; 

    }

    SECTION( "Atom '__init__'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"__init__ " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomNameNode>( root->GetRight() );

        REQUIRE( node->GetNameText()->GetText()->compare(L"__init__") == 0 );
        REQUIRE( node->GetNameText()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetNameText()->GetTokenEndPosition() == 8 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 9 ) ;    

    }

    SECTION( "Atom 'a'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomNameNode>( root->GetRight() );

        REQUIRE( node->GetNameText()->GetText()->compare(L"a") == 0 );
        REQUIRE( node->GetNameText()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetNameText()->GetTokenEndPosition() == 1 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 2 ) ;    

    }

    SECTION( "Atom '34e-8j'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"34e-8j " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomNumberNode>( root->GetRight() );

        REQUIRE( node->GetNumberText()->GetText()->compare(L"34e-8j") == 0 );
        REQUIRE( node->GetNumberText()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetNumberText()->GetTokenEndPosition() == 6 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "Atom '()'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"() " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomTupleNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftParen );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 1 );

        REQUIRE( node->GetRight() == nullptr );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyRightParen );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 1 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 2 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( "Atom '[]'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"[] " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomListNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftBracket );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 1 );

        REQUIRE( node->GetRight() == nullptr );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyRightBracket );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 1 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 2 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( "Atom '{}'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"{} " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomDictionaryNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftCurly );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 1 );

        REQUIRE( node->GetRight() == nullptr );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyRightCurly );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 1 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 2 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( "Atom '\"Test\"'" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"\"Test\" " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomStringNode>( root->GetRight() );

        auto units = node->GetStringNodes();
        
        REQUIRE(units->size() == 1);
        REQUIRE(units->at(0)->GetText()->compare(L"\"Test\"") == 0);
        REQUIRE(units->at(0)->GetTokenStartPosition() == 0);
        REQUIRE(units->at(0)->GetTokenEndPosition() == 6);

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "Atom '\"Test\" 'Again''" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"\"Test\" 'Again' " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomStringNode>( root->GetRight() );

        auto units = node->GetStringNodes();
        
        REQUIRE(units->size() == 2);
        REQUIRE(units->at(0)->GetText()->compare(L"\"Test\"") == 0);
        REQUIRE(units->at(0)->GetTokenStartPosition() == 0);
        REQUIRE(units->at(0)->GetTokenEndPosition() == 6);

        REQUIRE(units->at(1)->GetText()->compare(L"'Again'") == 0);
        REQUIRE(units->at(1)->GetTokenStartPosition() == 7);
        REQUIRE(units->at(1)->GetTokenEndPosition() == 14);

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 15 ) ; 

    }

    SECTION( "Atom failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"@" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 0);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyMatrice);
            REQUIRE(err->GetExceptionText()->compare(L"Illegal literal found!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: AtomExpr", "Parser - Expression rules" )
{

    SECTION( "await test" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"await test " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyAwait );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 5 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"test") == 0 );

        REQUIRE( node->GetRight() == nullptr );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 11 ) ; 

    }

    SECTION( "await test()" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"await test() " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyAwait );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 5 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"test") == 0 );

        auto trailers = node->GetRight();
        REQUIRE( trailers->size() == 1 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 13 ) ; 

    }

    SECTION( "test()" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"test() " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

        REQUIRE( node->GetOperator() == nullptr );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"test") == 0 );

        auto trailers = node->GetRight();
        REQUIRE( trailers->size() == 1 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

}


TEST_CASE( "Rule: Power", "Parser - Expression rules" )
{

    SECTION( " a ** b"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a ** b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::PowerNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyPower );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

}


TEST_CASE( "Rule: Factor", "Parser - Expression rules" )
{

    SECTION( " + a "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"+a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::UnaryPlusNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 1 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( " - a "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"-a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::UnaryMinusNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMinus );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 1 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( " ~ a "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"~a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::UnaryBitInvertNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitInvert );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 1 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 3 ) ; 

    }

    SECTION( " + + a (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"++a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::UnaryPlusNode>( root->GetRight() );
        auto node2 = std::static_pointer_cast<AST::UnaryPlusNode>( node->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );
        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 4 ) ; 

    }

}


TEST_CASE( "Rule: Term", "Parser - Expression rules" )
{

    SECTION( "a * b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a * b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::MulNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMul );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a / b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a / b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::DivNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyDiv );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a % b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a % b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::ModuloNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyModulo );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a @ b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a @ b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::MatriceNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMatrice );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a // b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a // b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::FloorDivNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyFloorDiv );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a * b * c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a * b * c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::MulNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMul );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::MulNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyMul) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: Arith", "Parser - Expression rules" )
{

    SECTION( "a + b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a + b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::PlusNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a - b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a - b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::MinusNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMinus );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a + b - c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a + b - c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::MinusNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyMinus );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::PlusNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyPlus) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: Shift", "Parser - Expression rules" )
{

    SECTION( "a << b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a << b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::ShiftLeftNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyShiftLeft );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a >> b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a >> b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::ShiftRightNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyShiftRight );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a << b >> c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a << b >> c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::ShiftRightNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyShiftRight );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 7 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 9 );

        auto node2 = std::static_pointer_cast<AST::ShiftLeftNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyShiftLeft) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 4 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 12 ) ; 

    }

}


TEST_CASE( "Rule: AndExpr", "Parser - Expression rules" )
{

    SECTION( "a & b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a & b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitAndNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitAnd );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a & b & c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a & b & c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitAndNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitAnd );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::BitAndNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyBitAnd) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: XorExpr", "Parser - Expression rules" )
{

    SECTION( "a ^ b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a ^ b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitXorNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitXor );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a ^ b ^ c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a ^ b ^ c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitXorNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitXor );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::BitXorNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyBitXor) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: OrExpr", "Parser - Expression rules" )
{

    SECTION( "a | b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a | b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitOrNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitOr );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a | b | c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a | b | c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::BitOrNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyBitOr );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::BitOrNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyBitOr) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: Compariosn", "Parser - Expression rules" )
{

    SECTION( "a < b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a < b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareLessNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyLess );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a > b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a > b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareGreaterNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyGreater );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "a <= b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a <= b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareLessEqualNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyLessEqual );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a >= b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a >= b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareGreaterEqualNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyGreaterEqual );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a != b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a != b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareNotEqualNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyNotEqual );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a <> b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a <> b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareNotEqualNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyNotEqual );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a == b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a == b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareNotEqualNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyEqual );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a in b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a in b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareInNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyIn );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a is b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a is b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareIsNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyIs );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a is not b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a is not b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareIsNotNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyIs );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 4 );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyNot );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 5 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 8 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 11 ) ; 

    }

    SECTION( "a not in b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a not in b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareIsNotNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyNot );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 5 );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyIn );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 8 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 11 ) ; 

    }

    SECTION( "a < b > c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a < b > c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::CompareGreaterNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyGreater );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 6 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 7 );

        auto node2 = std::static_pointer_cast<AST::CompareLessNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyLess) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 3 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: NotTest", "Parser - Expression rules" )
{

    SECTION( "not a "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"not a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::NotTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyNot );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

    SECTION( "not not a "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"not not a " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::NotTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyNot );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 3 );

        auto node2 = std::static_pointer_cast<AST::NotTestNode>( node->GetRight() );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyNot );
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 4 );
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 7 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 10 ) ; 

    }

}


TEST_CASE( "Rule: AndTest", "Parser - Expression rules" )
{

    SECTION( "a and b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a and b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AndTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyAnd );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 5 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeftNode() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRightNode() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 8 ) ; 

    }

    SECTION( "a and b and c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a and b and c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AndTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyAnd );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 8 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 11 );

        auto node2 = std::static_pointer_cast<AST::AndTestNode>( node->GetLeftNode() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeftNode() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyAnd) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 5 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRightNode() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRightNode() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 14 ) ; 

    }

}


TEST_CASE( "Rule: OrTest", "Parser - Expression rules" )
{

    SECTION( "a or b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a or b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::OrTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyOr );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 4 );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 7 ) ; 

    }

    SECTION( "a or b or c (recursive)"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a or b or c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::OrTestNode>( root->GetRight() );

        REQUIRE( node->GetOperator()->GetSymbolKind() == TokenKind::PyOr );
        REQUIRE( node->GetOperator()->GetTokenStartPosition() == 7 );
        REQUIRE( node->GetOperator()->GetTokenEndPosition() == 9 );

        auto node2 = std::static_pointer_cast<AST::OrTestNode>( node->GetLeft() );

        auto leftFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        REQUIRE( leftFirst->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node2->GetOperator()->GetSymbolKind() == TokenKind::PyOr) ;
        REQUIRE( node2->GetOperator()->GetTokenStartPosition() == 2 ) ;
        REQUIRE( node2->GetOperator()->GetTokenEndPosition() == 4 ) ;

        auto rightFirst = std::static_pointer_cast<AST::AtomNameNode>( node2->GetRight() );
        REQUIRE( rightFirst->GetNameText()->GetText()->compare(L"b") == 0 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 12 ) ; 

    }

}


TEST_CASE( "Rule: Lambda", "Parser - Expression rules" )
{

    SECTION( "lambda a: a + 1 "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"lambda a: a + 1 " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::LambdaNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLambda );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 6 );
        
        auto left = std::static_pointer_cast<AST::VarArgsListExpressionNode>( node->GetLeft() );
        REQUIRE( left->GetNodes()->size() == 1 );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 8 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 9 );
        
        auto right = std::static_pointer_cast<AST::PlusNode>( node->GetRight() );
        auto op1 = std::static_pointer_cast<AST::PlusNode>( right );
        REQUIRE( op1->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 16 ) ; 

    }

    SECTION( "lambda : a + 1 "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"lambda : a + 1 " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::LambdaNode>( root->GetRight() );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLambda );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 0 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 6 );
        
        REQUIRE( node->GetLeft() == nullptr );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 7 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 8 );
        
        auto right = std::static_pointer_cast<AST::PlusNode>( node->GetRight() );
        auto op1 = std::static_pointer_cast<AST::PlusNode>( right );
        REQUIRE( op1->GetOperator()->GetSymbolKind() == TokenKind::PyPlus );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 15 ) ; 

    }

    SECTION( "Lambda failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"lambda a + 1 " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 9);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPlus); // Because 'a' is taken in VarArgs ....
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'lambda' expression!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: Test expression", "Parser - Expression rules" )
{

    SECTION( "a if b else c "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a if b else c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::TestNode>( root->GetRight() );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyIf );
        REQUIRE( node->GetOperator1()->GetTokenStartPosition() == 2 );
        REQUIRE( node->GetOperator1()->GetTokenEndPosition() == 4 );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( node->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( node->GetOperator2()->GetTokenStartPosition() == 7 );
        REQUIRE( node->GetOperator2()->GetTokenEndPosition() == 11 );

        auto next = std::static_pointer_cast<AST::AtomNameNode>( node->GetNext() );
        REQUIRE( next->GetNameText()->GetText()->compare(L"c") == 0 );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 14 ) ; 

    }

    SECTION( "Test expression failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a if b c " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 7);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::Name);
            REQUIRE(err->GetExceptionText()->compare(L"Missing 'else' in 'test expression!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: TestList", "Parser - Expression rules" )
{

    SECTION( "a, b "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a, b " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::TestListNode>( root->GetRight() );

        REQUIRE( node->GetNodes()->size() == 2 );

        auto node1 = std::static_pointer_cast<AST::AtomNameNode>( node->GetNodes()->at(0) );
        REQUIRE( node1->GetNameText()->GetText()->compare(L"a") == 0 );

        auto node2 = std::static_pointer_cast<AST::AtomNameNode>( node->GetNodes()->at(1) );
        REQUIRE( node2->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE( node->GetSeparators()->size() == 1 );
        REQUIRE( node->GetSeparators()->at(0)->GetSymbolKind() == TokenKind::PyComma );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 5 ) ; 

    }

    SECTION( "a, b, \r\n"  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a, b, \r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 1 );
        REQUIRE( root->GetNewlines()->at(0)->GetSymbolKind() == TokenKind::Newline );

        auto node = std::static_pointer_cast<AST::TestListNode>( root->GetRight() );

        REQUIRE( node->GetNodes()->size() == 2 );

        auto node1 = std::static_pointer_cast<AST::AtomNameNode>( node->GetNodes()->at(0) );
        REQUIRE( node1->GetNameText()->GetText()->compare(L"a") == 0 );

        auto node2 = std::static_pointer_cast<AST::AtomNameNode>( node->GetNodes()->at(1) );
        REQUIRE( node2->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE( node->GetSeparators()->size() == 2 );
        REQUIRE( node->GetSeparators()->at(0)->GetSymbolKind() == TokenKind::PyComma );
        REQUIRE( node->GetSeparators()->at(1)->GetSymbolKind() == TokenKind::PyComma );

        REQUIRE ( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( node->GetNodeEndPosition() == 6 ) ; 

    }

}
#include <iostream>

TEST_CASE( "Rule: Call with arguments", "Parser - Expression rules" )
{

    // SECTION( "a(b) "  )
    // {

    //     auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a(b) \r\n" ) );
    //     auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
    //     auto parser = std::make_shared<PythonCoreParser>(lexer);

    //     auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

    //     REQUIRE( root->GetNewlines()->size() == 1 );

    //     auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

    //     REQUIRE( node->GetOperator() == nullptr );

    //     auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
    //     REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

    //     auto trailers = node->GetRight();
    //     REQUIRE( trailers->size() == 1 );

    //     auto one = std::static_pointer_cast<AST::CallNode>( trailers->at(0) );

    //     REQUIRE( one->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftParen );
    //     REQUIRE( one->GetOperator1()->GetTokenStartPosition() == 1 );
    //     REQUIRE( one->GetOperator1()->GetTokenEndPosition() == 2 );

    //     REQUIRE( one->GetOperator2()->GetSymbolKind() == TokenKind::PyRightParen );
    //     REQUIRE( one->GetOperator2()->GetTokenStartPosition() == 3 );
    //     REQUIRE( one->GetOperator2()->GetTokenEndPosition() == 4 );

    //     REQUIRE( one->GetRight()->GetNodeStartPosition() == 2 );
    //     REQUIRE( one->GetRight()->GetNodeEndPosition() == 3 );

    //     auto elem = std::static_pointer_cast<AST::AtomNameNode>( one->GetRight() );
    //     REQUIRE( elem != nullptr );
    //     auto token = std::static_pointer_cast<NameToken>( elem->GetNameText() );
    //     REQUIRE( token != nullptr );

    //     REQUIRE( token->GetText() != nullptr );

    //     REQUIRE( node->GetNodeStartPosition() == 0 ) ;  
    //     REQUIRE( node->GetNodeEndPosition() == 5 ) ; 

    // }

    SECTION( "a(b) "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a(b) " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

        REQUIRE( node->GetOperator() == nullptr );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto trailers = node->GetRight();
        REQUIRE( trailers->size() == 1 );

        auto one = std::static_pointer_cast<AST::CallNode>( trailers->at(0) );

        REQUIRE( one->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftParen );
        REQUIRE( one->GetOperator1()->GetTokenStartPosition() == 1 );
        REQUIRE( one->GetOperator1()->GetTokenEndPosition() == 2 );

        REQUIRE( one->GetOperator2()->GetSymbolKind() == TokenKind::PyRightParen );
        REQUIRE( one->GetOperator2()->GetTokenStartPosition() == 3 );
        REQUIRE( one->GetOperator2()->GetTokenEndPosition() == 4 );

        REQUIRE( one->GetRight()->GetNodeStartPosition() == 2 );
        REQUIRE( one->GetRight()->GetNodeEndPosition() == 3 );

        auto elem = std::static_pointer_cast<AST::AtomNameNode>( one->GetRight() );
        REQUIRE( elem->GetNameText()->GetText()->compare(L"b") == 0 );

        REQUIRE( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE( node->GetNodeEndPosition() == 5 ) ; 

    }

    SECTION( "a(*b) "  )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"a(*b) " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );

        auto node = std::static_pointer_cast<AST::AtomExprNode>( root->GetRight() );

        REQUIRE( node->GetOperator() == nullptr );

        auto left = std::static_pointer_cast<AST::AtomNameNode>( node->GetLeft() );
        REQUIRE( left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto trailers = node->GetRight();
        REQUIRE( trailers->size() == 1 );

        auto one = std::static_pointer_cast<AST::CallNode>( trailers->at(0) );

        REQUIRE( one->GetOperator1()->GetSymbolKind() == TokenKind::PyLeftParen );
        REQUIRE( one->GetOperator1()->GetTokenStartPosition() == 1 );
        REQUIRE( one->GetOperator1()->GetTokenEndPosition() == 2 );

        REQUIRE( one->GetOperator2()->GetSymbolKind() == TokenKind::PyRightParen );
        REQUIRE( one->GetOperator2()->GetTokenStartPosition() == 4 );
        REQUIRE( one->GetOperator2()->GetTokenEndPosition() == 5 );

        auto elem = std::static_pointer_cast<AST::ArgumentNode>( one->GetRight() );
        REQUIRE( elem->GetOperator()->GetSymbolKind() == TokenKind::PyMul );

        auto right = std::static_pointer_cast<AST::AtomNameNode>( elem->GetRight() );
        REQUIRE( right->GetNameText()->GetText()->compare(L"b") == 0 );
       
        REQUIRE( node->GetNodeStartPosition() == 0 ) ;  
        REQUIRE( node->GetNodeEndPosition() == 6 ) ; 

    }

}