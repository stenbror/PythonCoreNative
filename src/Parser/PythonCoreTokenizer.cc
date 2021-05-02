
#include <PythonCoreTokenizer.h>

using namespace PythonCoreNative::RunTime::Parser;

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