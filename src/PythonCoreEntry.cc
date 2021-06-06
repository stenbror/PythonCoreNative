
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
        
        auto sourceBuffer = std::make_shared<SourceBuffer>( std::make_shared<std::wstring>( L"if a: pass\r\nelse: pass\r\n\r\n" ) );
        auto lexer = std::make_shared<PythonCoreTokenizer>(4, sourceBuffer);
        auto parser = std::make_shared<PythonCoreParser>(lexer);
        
        parser->ParseFileInput();

        
        

    }
    catch (std::shared_ptr<LexicalError> err)
    {
        std::wcout <<  err->ExceptionText()->data() << " : " << err->ExceptionPosition() << L"\r\n";
    }
    catch (std::shared_ptr<SyntaxError> err)
    {
        std::wcout <<  err->GetExceptionText()->data() << " : " << err->GetPosition() << L"\r\n";
    }

    ///////////////////////////////////////////////////////////////////////////
    
    return 0;
}