
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

    }

}