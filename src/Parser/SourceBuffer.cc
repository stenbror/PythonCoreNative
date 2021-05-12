#include <SourceBuffer.h>

using namespace PythonCoreNative::RunTime::Parser;

SourceBuffer::SourceBuffer()
{

}

wchar_t SourceBuffer::GetChar()
{
    return L'\0';
}

wchar_t SourceBuffer::PeekChar()
{
    return L'\0';
}

void SourceBuffer::UngetChar(wchar_t ch)
{

}

unsigned int SourceBuffer::BufferPosition()
{
    return 0;
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
    
}
