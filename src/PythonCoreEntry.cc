
#include <PythonCore.h>
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

int PythonCoreEntry(int argc, char *argv[], std::wstring systemName)
{

    std::wcout << L"PythonCore " << systemName << L" [Development!]" << L"\r\n";
    std::wcout << L"Written by Richard Magnor Stenbro. https://github.com/stenbror/PythonCoreNative\r\n\r\n";

    // Testing area for now /////////////////////////////////////////////////

    try
    {
        
        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"0b_111_011 " ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);

        lexer->Advance();

        auto txt = std::static_pointer_cast<NumberToken>( lexer->CurSymbol() )->GetText()->data();

        std::wcout << txt << L"\r\n";

    }
    catch (std::shared_ptr<LexicalError> err)
    {
        std::wcout <<  err->ExceptionText()->data() << " : " << err->ExceptionPosition() << L"\r\n";
    }

    ///////////////////////////////////////////////////////////////////////////
    
    return 0;
}