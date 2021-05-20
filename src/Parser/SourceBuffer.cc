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
    wchar_t ch = mSourceCode->at(mIndex);

    return  ( ch >= L'a' && ch <= L'z' ) ||
            ( ch >= L'A' && ch <= L'Z' ) ||
            ch == L'_';
}

bool SourceBuffer::IsLiteralOrNumberCharacter()
{
    wchar_t ch = mSourceCode->at(mIndex);

    return  (ch >= L'0' && ch <= L'9' ) ||
            IsLiteralStartCharacter();
}

bool SourceBuffer::IsHexDigit()
{
    wchar_t ch = mSourceCode->at(mIndex);

    return  (ch >= L'0' && ch <= L'9') ||
            (ch >= L'a' && ch <= L'f') ||
            (ch >= L'A' && ch <= L'F');
}

bool SourceBuffer::IsOctetDigit()
{
    wchar_t ch = mSourceCode->at(mIndex);

    return  (ch >= L'0' && ch <= L'7');
}

bool SourceBuffer::IsBinaryDigit()
{
    wchar_t ch = mSourceCode->at(mIndex);

    return ch == L'0' || ch == L'1';
}

bool SourceBuffer::IsDigit()
{
    wchar_t ch = mSourceCode->at(mIndex);

    return ch >= L'0' && ch <= L'9';
}

void SourceBuffer::Next()
{
    mIndex++;
}
