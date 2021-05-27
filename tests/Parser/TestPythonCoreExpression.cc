
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

}