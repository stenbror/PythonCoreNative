
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

PythonCoreParser::PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer)
{
    mLexer = lexer;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseEvalInput()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFileInput()
{
    return nullptr;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSingleInput()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncTypeInput()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncType()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseTypeList()
{
    return nullptr;
}