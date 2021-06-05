
#include <catch2/catch.hpp>

#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

TEST_CASE( "Rule: EvalInput", "Parser - Toplevel rules" )
{

    SECTION( "EvalInput start test" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"lambda a : a * a\r\n\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseEvalInput() );

        REQUIRE( root->GetNewlines()->size() == 2 );
        REQUIRE( root->GetNewlines()->at(0)->GetSymbolKind() == TokenKind::Newline );
        REQUIRE( root->GetNewlines()->at(0)->GetTokenStartPosition() == 16 );
        REQUIRE( root->GetNewlines()->at(0)->GetTokenEndPosition() == 18 );
        
        REQUIRE( root->GetNewlines()->at(1)->GetSymbolKind() == TokenKind::Newline );
        REQUIRE( root->GetNewlines()->at(1)->GetTokenStartPosition() == 18 );
        REQUIRE( root->GetNewlines()->at(1)->GetTokenEndPosition() == 20 );

        auto node = std::static_pointer_cast<AST::LambdaNode>( root->GetRight() );
        REQUIRE( node->GetOperator1()->GetSymbolKind() == TokenKind::PyLambda );
        REQUIRE( node->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto right = std::static_pointer_cast<AST::MulNode>( node->GetRight() );
        REQUIRE( right->GetOperator()->GetTriviaList()->size() == 1 );
        
        auto right_left = std::static_pointer_cast<AST::AtomNameNode>( right->GetLeft() );
        REQUIRE( right_left->GetNameText()->GetTriviaList()->size() == 1 );

        auto right_right = std::static_pointer_cast<AST::AtomNameNode>( right->GetRight() );
        REQUIRE( right_right->GetNameText()->GetTriviaList()->size() == 1 );

        auto trivia = std::static_pointer_cast<WhiteSpaceTrivia>(right_right->GetNameText()->GetTriviaList()->at(0) );
        REQUIRE( trivia->GetStartPosition() == 14 );
        REQUIRE( trivia->GetEndPosition() == 15 );
        REQUIRE( trivia->GetWhiteChar() == L' ' );
        
        REQUIRE ( root->GetNodeStartPosition() == 0 ) ;  
        REQUIRE ( root->GetNodeEndPosition() == 20 ) ; 

    }

}

