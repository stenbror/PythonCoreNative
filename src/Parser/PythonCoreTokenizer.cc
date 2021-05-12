
#include <PythonCoreTokenizer.h>

using namespace PythonCoreNative::RunTime::Parser;



PythonCoreTokenizer::PythonCoreTokenizer(unsigned int tabSize, std::shared_ptr<SourceBuffer> sourceBuffer)
{
    //auto remove = mReservedKeywords.find(U"as");
}

std::shared_ptr<Token> PythonCoreTokenizer::CurSymbol()
{
    return mCurSymbol;
}
            
unsigned int PythonCoreTokenizer::Position()
{
    return 0;
}
            
void PythonCoreTokenizer::Advance()
{
    // More.
}