#include <SourceBuffer.h>

using namespace PythonCoreNative::RunTime::Parser;

SourceBuffer::SourceBuffer()
{

}

char32_t SourceBuffer::GetChar()
{
    return U'\0';
}

void SourceBuffer::UngetChar(char32_t ch)
{

}

bool inline SourceBuffer::IsLiteralStartCharacter(char32_t ch)
{
    return false; // Dummy for now!
}

bool inline SourceBuffer::IsLiteralOrNumberCharacter(char32_t ch)
{
    return false; // Dummy for now!
}

bool inline SourceBuffer::IsHexDigit(char32_t ch)
{
    return false; // Dummy for now!
}

bool inline SourceBuffer::IsOctetDigit(char32_t ch)
{
    return false; // Dummy for now!
}

bool inline SourceBuffer::IsBinaryDigit(char32_t ch)
{
    return false; // Dummy for now!
}

bool inline SourceBuffer::IsDigit(char32_t ch)
{
    return false; // Dummy for now!
}
