#include <SourceBuffer.h>

using namespace PythonCoreNative::RunTime::Parser;

SourceBuffer::SourceBuffer(std::shared_ptr<std::wstring> buf)
{
    mSourceCode = buf;
    mIndex = 0;
}

wchar_t SourceBuffer::GetChar()
{

    try
    {

        return mSourceCode->at(mIndex++);
    
    }
    catch(const std::out_of_range& e)
    {

        return L'\0';
    
    }
    
}

wchar_t SourceBuffer::PeekChar()
{
    
    try
    {

        return mSourceCode->at(mIndex + 1);
    
    }
    catch(const std::out_of_range& e)
    {

        return L'\0';
    
    }

}

void SourceBuffer::UngetChar(wchar_t ch)
{
    if (mIndex > 0 && mSourceCode->at(mIndex - 1) == ch) mIndex--;
}

unsigned int SourceBuffer::BufferPosition()
{
    return mIndex;
}

void SourceBuffer::SetPosition(unsigned int pos)
{
    mIndex = pos;
}

bool SourceBuffer::IsLiteralStartCharacter()
{
    return false; // Dummy for now!
}

bool SourceBuffer::IsLiteralOrNumberCharacter()
{
    return false; // Dummy for now!
}

bool SourceBuffer::IsHexDigit()
{
    return false; // Dummy for now!
}

bool SourceBuffer::IsOctetDigit()
{
    return false; // Dummy for now!
}

bool SourceBuffer::IsBinaryDigit()
{
    return false; // Dummy for now!
}

bool SourceBuffer::IsDigit()
{
    return false; // Dummy for now!
}

void SourceBuffer::Next()
{
    mIndex++;
}
