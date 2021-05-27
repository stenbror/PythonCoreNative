
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