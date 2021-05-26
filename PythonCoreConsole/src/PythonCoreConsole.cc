
#include <PythonCoreParser.h>

#include <iostream>

using namespace PythonCoreNative::RunTime::Parser;

int main(int argc, char *argv[])
{
    std::wcout << L"PythonCore ( Console ) \r\n";
    std::wcout << L"Written by Richard Magnor Stenbro. https://github.com/stenbror/PythonCoreNative\r\n\r\n";

    auto buf = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>(L"as ") );
    auto lexer = std::make_shared<PythonCoreTokenizer>( 4, buf );

    lexer->Advance();
    return 0;
}