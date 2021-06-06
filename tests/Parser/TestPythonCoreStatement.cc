
#include <catch2/catch.hpp>

#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;


TEST_CASE( "Rule: if/elif/else", "Parser - Statement rules" )
{

    SECTION( "if a: pass" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::IfStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyIf );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );

        auto el1_right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNodes()->size() == 1 );        
        REQUIRE( el1_right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( el1_right->GetOperator1()->GetSymbolKind() == TokenKind::Newline );


        REQUIRE( elem1->GetElifNodes()->size() == 0 );
        REQUIRE( elem1->GetElseNode() == nullptr );


        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 12 );

    }

    SECTION( "if a: pass\r\nelse: pass\r\n" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelse: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::IfStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyIf );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );

        auto el1_right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNodes()->size() == 1 );        
        REQUIRE( el1_right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( el1_right->GetOperator1()->GetSymbolKind() == TokenKind::Newline );


        REQUIRE( elem1->GetElifNodes()->size() == 0 );
        
        auto elsePart = std::static_pointer_cast<AST::ElseStatementNode>( elem1->GetElseNode() );
        REQUIRE( elsePart->GetOperator1()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( elsePart->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto elseTxt = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( elseTxt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 24 );

    }

    SECTION( "if a: pass\r\elif b: pass\r\nnelse: pass\r\n" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelif b: pass\r\nelse: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::IfStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyIf );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );

        auto el1_right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNodes()->size() == 1 );        
        REQUIRE( el1_right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( el1_right->GetOperator1()->GetSymbolKind() == TokenKind::Newline );


        REQUIRE( elem1->GetElifNodes()->size() == 1 );
        auto node1 = std::static_pointer_cast<AST::ElifStatementNode>( elem1->GetElifNodes()->at(0) );
        REQUIRE( node1->GetOperator1()->GetSymbolKind() == TokenKind::PyElif );
        REQUIRE( node1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto node1_left = std::static_pointer_cast<AST::AtomNameNode>( node1->GetLeft() );
        auto node1_right = std::static_pointer_cast<AST::SimpleStatementNode>( node1->GetRight() );
        auto node1_right_txt = std::static_pointer_cast<AST::PassStatementNode>( node1_right->GetNodes()->at(0) );
        REQUIRE( node1_left->GetNameText()->GetText()->compare(L"b") == 0 );
        REQUIRE( node1_right_txt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );
        
        auto elsePart = std::static_pointer_cast<AST::ElseStatementNode>( elem1->GetElseNode() );
        REQUIRE( elsePart->GetOperator1()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( elsePart->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto elseTxt = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( elseTxt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 38 );

    }

}

