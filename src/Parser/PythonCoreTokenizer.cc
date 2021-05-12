
#include <PythonCoreTokenizer.h>

using namespace PythonCoreNative::RunTime::Parser;



PythonCoreTokenizer::PythonCoreTokenizer(unsigned int tabSize, std::shared_ptr<SourceBuffer> sourceBuffer)
{
    if (sourceBuffer == nullptr) throw ;

    mSourceBuffer = sourceBuffer;
    mPosition = mSourceBuffer->BufferPosition();
    
}

std::shared_ptr<Token> PythonCoreTokenizer::CurSymbol()
{
    return mCurSymbol;
}
            
unsigned int PythonCoreTokenizer::Position()
{
    return mSourceBuffer->BufferPosition();
}
            
void PythonCoreTokenizer::Advance()
{
    

    /* Handle reserved keywords or Literal names here */
    if (mSourceBuffer->IsLiteralStartCharacter() || mSourceBuffer->PeekChar() == '_')
    {
        mPosition = mSourceBuffer->BufferPosition();

        std::wstringstream buffer;

        while (mSourceBuffer->IsLiteralOrNumberCharacter() || mSourceBuffer->PeekChar() == '_' )
        {
            buffer << mSourceBuffer->GetChar();
        }

        std::wstring key = buffer.str(); 
        
        if (mReservedKeywords.find(key) != mReservedKeywords.end() )
        {
            mCurSymbol = std::make_shared<Token>(mPosition, mSourceBuffer->BufferPosition(), mReservedKeywords.at(key));
            
            return ;
        }
        else if (mSourceBuffer->PeekChar() == L'"' || mSourceBuffer->PeekChar() == L'\'')
        {

        }
        else
        {
            mCurSymbol = std::make_shared<NameToken>(
                mPosition, 
                mSourceBuffer->BufferPosition(), 
                std::make_shared<std::wstring>(key));
            
            return;
        }
    }
}