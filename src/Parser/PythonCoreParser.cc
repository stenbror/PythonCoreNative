
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

PythonCoreParser::PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer)
{
    mLexer = lexer;
}
