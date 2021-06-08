
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

    SECTION( "if a: pass\r\nelif b: pass\r\nelif c: pass\r\nnelse: pass\r\n" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelif b: pass\r\nelif c: pass\r\nelse: pass\r\n" ) );
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


        REQUIRE( elem1->GetElifNodes()->size() == 2 );

        auto node1 = std::static_pointer_cast<AST::ElifStatementNode>( elem1->GetElifNodes()->at(0) );
        REQUIRE( node1->GetOperator1()->GetSymbolKind() == TokenKind::PyElif );
        REQUIRE( node1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto node1_left = std::static_pointer_cast<AST::AtomNameNode>( node1->GetLeft() );
        auto node1_right = std::static_pointer_cast<AST::SimpleStatementNode>( node1->GetRight() );
        auto node1_right_txt = std::static_pointer_cast<AST::PassStatementNode>( node1_right->GetNodes()->at(0) );
        REQUIRE( node1_left->GetNameText()->GetText()->compare(L"b") == 0 );
        REQUIRE( node1_right_txt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        auto node2 = std::static_pointer_cast<AST::ElifStatementNode>( elem1->GetElifNodes()->at(1) );
        REQUIRE( node2->GetOperator1()->GetSymbolKind() == TokenKind::PyElif );
        REQUIRE( node2->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto node2_left = std::static_pointer_cast<AST::AtomNameNode>( node2->GetLeft() );
        auto node2_right = std::static_pointer_cast<AST::SimpleStatementNode>( node2->GetRight() );
        auto node2_right_txt = std::static_pointer_cast<AST::PassStatementNode>( node2_right->GetNodes()->at(0) );
        REQUIRE( node2_left->GetNameText()->GetText()->compare(L"c") == 0 );
        REQUIRE( node2_right_txt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );
        
        auto elsePart = std::static_pointer_cast<AST::ElseStatementNode>( elem1->GetElseNode() );
        REQUIRE( elsePart->GetOperator1()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( elsePart->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto elseTxt = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( elseTxt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 52 );

    }

    SECTION( "if a: pass\r\nelif b: pass\r\n" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelif b: pass\r\n" ) );
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

        REQUIRE( elem1->GetElseNode() == nullptr );
        
        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 26 );

    }

    SECTION( "Missing ':' in 'if' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 5);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPass);
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'if' statement!") == 0);
        }
        
    }

    SECTION( "Missing ':' in 'elif' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelif b pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 19);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPass);
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'elif' statement!") == 0);
        }
        
    }

    SECTION( "Missing ':' in 'else' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelif b: pass\r\nelse pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 31);
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPass);
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'else' statement!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: while", "Parser - Statement rules" )
{

    SECTION( "while a: pass" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"while a: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::WhileStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyWhile );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );

        auto el1_right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNodes()->size() == 1 );        
        REQUIRE( el1_right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( el1_right->GetOperator1()->GetSymbolKind() == TokenKind::Newline );

        REQUIRE( elem1->GetNext() == nullptr );


        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 15 );

    }

     SECTION( "while a: pass\r\nelse: pass\r\n" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"while a: pass\r\nelse: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::WhileStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyWhile );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );

        auto el1_right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNodes()->size() == 1 );        
        REQUIRE( el1_right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( el1_right->GetOperator1()->GetSymbolKind() == TokenKind::Newline );

        auto elsePart = std::static_pointer_cast<AST::ElseStatementNode>( elem1->GetNext() );
        REQUIRE( elsePart->GetOperator1()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( elsePart->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        auto elseTxt = std::static_pointer_cast<AST::PassStatementNode>( el1_right->GetNodes()->at(0) );
        REQUIRE( elseTxt->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 27 );

    }

    SECTION( "Missing ':' in 'while' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"while a pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 8 );
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPass);
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'while' statement!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: for", "Parser - Statement rules" )
{

    SECTION( "for a in b: pass" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"for a in b: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::ForStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyFor );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyIn );
        REQUIRE( elem1->GetOperator3()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( elem1->GetOperator4() == nullptr ); // TypeComment

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );
        REQUIRE( el1_left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto el1_right = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNameText()->GetText()->compare(L"b") == 0 );

        auto el1_next = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetNext() );
        REQUIRE( el1_next->GetNodes()->size() == 1 );        
        REQUIRE( el1_next->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_next->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        REQUIRE( elem1->GetExtra() == nullptr );

        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 18 );

    }

    SECTION( "for a in b: passr\nelse: pass" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"for a in b: pass\r\nelse: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );

        
        auto elem1 = std::static_pointer_cast<AST::ForStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyFor );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyIn );
        REQUIRE( elem1->GetOperator3()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( elem1->GetOperator4() == nullptr ); // TypeComment

        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );
        REQUIRE( el1_left->GetNameText()->GetText()->compare(L"a") == 0 );

        auto el1_right = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetRight() );
        REQUIRE( el1_right->GetNameText()->GetText()->compare(L"b") == 0 );

        auto el1_next = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetNext() );
        REQUIRE( el1_next->GetNodes()->size() == 1 );        
        REQUIRE( el1_next->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_next->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

        auto elsePart = std::static_pointer_cast<AST::ElseStatementNode>( elem1->GetExtra() );
        REQUIRE( elsePart->GetOperator1()->GetSymbolKind() == TokenKind::PyElse );
        REQUIRE( elsePart->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        
        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 30 );

    }

    // SECTION( "for a in b: # type: int \r\n pass" )
    // {

    //     auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"for a in b: # type: int \r\n pass\r\n" ) );
    //     auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
    //     auto parser = std::make_shared<PythonCoreParser>(lexer);

    //     auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

    //     REQUIRE( root->GetNewlines()->size() == 0 );
    //     REQUIRE( root->GetNodes()->size() == 1 );

        
    //     auto elem1 = std::static_pointer_cast<AST::ForStatementNode>( root->GetNodes()->at(0) );
    //     REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyFor );
    //     REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyIn );
    //     REQUIRE( elem1->GetOperator3()->GetSymbolKind() == TokenKind::PyColon );
    //     REQUIRE( elem1->GetOperator4()->GetSymbolKind() == TokenKind::TypeComment );

    //     auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetLeft() );
    //     REQUIRE( el1_left->GetNameText()->GetText()->compare(L"a") == 0 );

    //     auto el1_right = std::static_pointer_cast<AST::AtomNameNode>( elem1->GetRight() );
    //     REQUIRE( el1_right->GetNameText()->GetText()->compare(L"b") == 0 );

    //     auto el1_next = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetNext() );
    //     REQUIRE( el1_next->GetNodes()->size() == 1 );        
    //     REQUIRE( el1_next->GetSeparators()->size() == 0 );

    //     auto item1 = std::static_pointer_cast<AST::PassStatementNode>( el1_next->GetNodes()->at(0) );
    //     REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );

    //     REQUIRE( elem1->GetExtra() == nullptr );

    //     REQUIRE( elem1->GetNodeStartPosition() == 0 );
    //     REQUIRE( elem1->GetNodeEndPosition() == 33 );

    // }

    SECTION( "Missing ':' in 'for' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"for a in b pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 11 );
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::PyPass);
            REQUIRE(err->GetExceptionText()->compare(L"Missing ':' in 'for' statement!") == 0);
        }
        
    }

    SECTION( "Missing 'in' in 'for' failes" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"for a b: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        try
        {
            auto root = std::static_pointer_cast<AST::EvalInputNode>( parser->ParseFileInput() );

            REQUIRE( false );

        }
        catch( std::shared_ptr<SyntaxError> err )
        {
            REQUIRE(err->GetPosition() == 6 );
            REQUIRE(err->GetFailureSymbol()->GetSymbolKind() == TokenKind::Name);
            REQUIRE(err->GetExceptionText()->compare(L"Missing 'in' in 'for' statement!") == 0);
        }
        
    }

}


TEST_CASE( "Rule: with", "Parser - Statement rules" )
{

    SECTION( "with a: pass" )
    {

        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"with a: pass\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);

        auto root = std::static_pointer_cast<AST::FileInputNode>( parser->ParseFileInput() );

        REQUIRE( root->GetNewlines()->size() == 0 );
        REQUIRE( root->GetNodes()->size() == 1 );
 
        auto elem1 = std::static_pointer_cast<AST::WithStatementNode>( root->GetNodes()->at(0) );
        REQUIRE( elem1->GetOperator1()->GetSymbolKind() == TokenKind::PyWith );
        REQUIRE( elem1->GetOpenParenthesis() == nullptr );
        REQUIRE( elem1->GetCloseParenthesis() == nullptr );
        REQUIRE( elem1->GetOperator2()->GetSymbolKind() == TokenKind::PyColon );
        REQUIRE( elem1->GetOperator3() == nullptr );

        auto nodes = elem1->GetWithItems();
        auto separators = elem1->GetSeparators();
        REQUIRE( nodes->size() == 1 );
        REQUIRE( separators->size() == 0 );

        auto el1 = std::static_pointer_cast<AST::WithItemStatementNode>( nodes->at(0) );
        auto el1_left = std::static_pointer_cast<AST::AtomNameNode>( el1->GetLeft() );
        REQUIRE( el1_left->GetNameText()->GetText()->compare(L"a") == 0 );
        REQUIRE( el1->GetOperator() == nullptr );
        REQUIRE( el1->GetRight() == nullptr );

        auto right = std::static_pointer_cast<AST::SimpleStatementNode>( elem1->GetRight() );
        REQUIRE( right->GetNodes()->size() == 1 );        
        REQUIRE( right->GetSeparators()->size() == 0 );

        auto item1 = std::static_pointer_cast<AST::PassStatementNode>( right->GetNodes()->at(0) );
        REQUIRE( item1->GetOperator()->GetSymbolKind() == TokenKind::PyPass );
        
        REQUIRE( elem1->GetNodeStartPosition() == 0 );
        REQUIRE( elem1->GetNodeEndPosition() == 14 );

    }

}

