
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

_nextLine:  

    mIsBlankLine = false;

    /* Analyze start of source code line */
    if (mAtBOL)
    {

        mAtBOL = false;
        unsigned int col = 0;

        while (mSourceBuffer->PeekChar() == ' ' || mSourceBuffer->PeekChar() == '\v' || mSourceBuffer->PeekChar() == '\t')
        {

            switch (mSourceBuffer->PeekChar())
            {
                case ' ':
                    col++;
                    break;
                case '\t':
                    col = (col / mTabSize + 1) * mTabSize;
                    break;
                case '\v':
                    col = 0;
                    break;
            }

            mSourceBuffer->Next();

        }

        if (    mSourceBuffer->PeekChar() == '#' || 
                mSourceBuffer->PeekChar() == '\r' || 
                mSourceBuffer->PeekChar() == '\n' || 
                mSourceBuffer->PeekChar() == '\\')
        {

        }

        if (!mIsBlankLine && mLevelStack.empty())
        {

            if (col == mIndentLevel.top())
            {
                // No change in indentaation levels.
            }
            else if (col > mIndentLevel.top())
            {

                mPending++;
                mIndentLevel.push(col);

            }
            else
            {

                while (mIndentLevel.size() > 0 && col < mIndentLevel.top())
                {

                    mPending--;
                    mIndentLevel.pop();

                }

                if (col != mIndentLevel.top())
                    throw std::make_shared<LexicalError>(
                        mSourceBuffer->BufferPosition(),
                        std::make_shared<std::wstring>(L"Inconsitant indentation level!")
                    );

            }

        }

    }

    mPosition = mSourceBuffer->BufferPosition();

    /* Handling indent or dedent(s) */
    if (mPending != 0)
    {

        if (mPending < 0)
        {
            mPending++;

            mCurSymbol = std::make_shared<Token>(
                mPosition,
                mSourceBuffer->BufferPosition(),
                TokenKind::Dedent);
        }
        else
        {

            mPending--;

            mCurSymbol = std::make_shared<Token>(
                mPosition,
                mSourceBuffer->BufferPosition(),
                TokenKind::Indent);

        }

        return;

    }

_again:

    mPosition = mSourceBuffer->BufferPosition();

    /* Handle whitespace and other trivia */
    while (mSourceBuffer->PeekChar() == ' ' || mSourceBuffer->PeekChar() == '\v' || mSourceBuffer->PeekChar() == '\t')
    {
        auto ch = mSourceBuffer->GetChar();
        switch (ch) // Trivia handling below later!
        {
            case ' ':
            case '\t':
            default:
                break;
        }
    }

    mPosition = mSourceBuffer->BufferPosition();

    /* Handle comment and type comment */
    if (mSourceBuffer->PeekChar() == '#')
    {
        std::wstringstream buffer;

        while ( mSourceBuffer->PeekChar() != '\r' ||
                mSourceBuffer->PeekChar() != '\n' ||
                mSourceBuffer->PeekChar() != '\0' ) buffer << mSourceBuffer->GetChar();

        std::wstring key = buffer.str(); 

        if (key.find_first_of(L"# type: ", 0, sizeof(wchar_t)) == 0)
        {
            /* Type Comments starts with '# type: ' */
            mCurSymbol = std::make_shared<TypeCommentToken>(
                mPosition, 
                mSourceBuffer->BufferPosition(), 
                std::make_shared<std::wstring>(key));

            return ;
        }

        // ADD: Trivia collecting comment.

        goto _again;
    }


    /* Handle End of File */
    if (mSourceBuffer->PeekChar() == '\0')
    {
        // Add check for interactive mode later!

        mCurSymbol = std::make_shared<Token>(   
            mPosition,
            mSourceBuffer->BufferPosition(),
            TokenKind::EndOfFile);

        return;
    }
    

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
        else if (mSourceBuffer->PeekChar() == '"' || mSourceBuffer->PeekChar() == '\'')
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


    /* Handle Newline as Token or trivia */
    if (mSourceBuffer->PeekChar() == '\r' || mSourceBuffer->PeekChar() == '\n')
    {
        mAtBOL = true;

        wchar_t ch1 = mSourceBuffer->PeekChar() == '\r' ? mSourceBuffer->GetChar() : ' ', 
                ch2 = mSourceBuffer->PeekChar() == '\n' ? mSourceBuffer->GetChar() : ' ';

        if (mSourceBuffer->PeekChar() != '\0' && (mIsBlankLine || !mLevelStack.empty()))
        {
            // Add Trivia handling here later. Save ch1, ch2 as trivia as needed.

            goto _nextLine;
        }

        mCurSymbol = std::make_shared<Token>(
            mPosition,
            mSourceBuffer->BufferPosition(),
            TokenKind::Newline);

        return;
    }


    /* Handle period, elipsis or start of number */
    if (mSourceBuffer->PeekChar() == '.')
    {
        mPosition = mSourceBuffer->BufferPosition();

        mSourceBuffer->Next();

        if (mSourceBuffer->PeekChar() == '.')
        {
            mSourceBuffer->Next();

            if (mSourceBuffer->PeekChar() == '.')
            {
                mSourceBuffer->Next();

                mCurSymbol = std::make_shared<Token>(
                    mPosition,
                    mSourceBuffer->BufferPosition(),
                    TokenKind::PyElipsis);

                return;
            }
            else 
                throw std::make_shared<LexicalError>(
                    mSourceBuffer->BufferPosition(),
                    std::make_shared<std::wstring>(L"Missing one '.' in elipsis operator '...' or uneeded '.'") );
        }
        else if (!mSourceBuffer->IsDigit())
        {
            mCurSymbol = std::make_shared<Token>(
                    mPosition,
                    mSourceBuffer->BufferPosition(),
                    TokenKind::PyDot);

                return;
        }

        mSourceBuffer->UngetChar(L'.');
    }


    /* Handle numbers */
    if (mSourceBuffer->IsDigit() || mSourceBuffer->PeekChar() == '.')
    {
        mPosition = mSourceBuffer->BufferPosition();

        std::wstringstream buffer;

        if (mSourceBuffer->PeekChar() == '0')
        {
            buffer << mSourceBuffer->GetChar();

            if (mSourceBuffer->PeekChar() == 'x' || mSourceBuffer->GetChar() == 'X')
            {
                
                buffer << mSourceBuffer->GetChar();

                do
                {
                    
                    if (mSourceBuffer->PeekChar() == '_') buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsHexDigit()) 
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expecting hexadecimal digits!"));

                    do
                    {
                        
                        buffer << mSourceBuffer->GetChar();

                    } while (mSourceBuffer->IsHexDigit());
                    

                } while (mSourceBuffer->PeekChar() == '_');
                
            }

            else if (mSourceBuffer->PeekChar() == 'o' || mSourceBuffer->GetChar() == 'O')
            {

                buffer << mSourceBuffer->GetChar();

                do
                {
                    
                    if (mSourceBuffer->PeekChar() == '_') buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsOctetDigit()) 
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expecting octet digits!"));

                    do
                    {
                        
                        buffer << mSourceBuffer->GetChar();

                    } while (mSourceBuffer->IsOctetDigit());
                    

                } while (mSourceBuffer->PeekChar() == '_');

                if (!mSourceBuffer->IsDigit()) 
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expecting octet digits!"));

            }

            else if (mSourceBuffer->PeekChar() == 'b' || mSourceBuffer->GetChar() == 'B')
            {

                buffer << mSourceBuffer->GetChar();

                do
                {
                    
                    if (mSourceBuffer->PeekChar() == '_') buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsBinaryDigit()) 
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expecting binary digits!"));

                    do
                    {
                        
                        buffer << mSourceBuffer->GetChar();

                    } while (mSourceBuffer->IsBinaryDigit());
                    

                } while (mSourceBuffer->PeekChar() == '_');

                if (!mSourceBuffer->IsDigit()) 
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expecting binary digits!"));

            }

            else
            {

                auto nonZero = false;

                if (mSourceBuffer->PeekChar() != '.')
                {

                    while (true)
                    {

                        while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                        if (mSourceBuffer->PeekChar() != '_') break;

                        buffer << mSourceBuffer->GetChar();

                        if (!mSourceBuffer->IsDigit())
                            throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                    }
                }

                if (mSourceBuffer->PeekChar() == '.')
                {

                    buffer << mSourceBuffer->GetChar();

                    while (true)
                    {

                        while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                        if (mSourceBuffer->PeekChar() != '_') break;

                        buffer << mSourceBuffer->GetChar();

                        if (!mSourceBuffer->IsDigit())
                            throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                    }

                }

                if (mSourceBuffer->PeekChar() == 'e' || mSourceBuffer->PeekChar() == 'E')
                {

                    buffer << mSourceBuffer->GetChar();

                    if (mSourceBuffer->PeekChar() == '+' || mSourceBuffer->PeekChar() == '-')
                    {

                        buffer << mSourceBuffer->GetChar();

                        if (!mSourceBuffer->IsDigit())
                            throw std::make_shared<LexicalError>(
                                    mSourceBuffer->BufferPosition(),
                                    std::make_shared<std::wstring>(L"Expected digit after '+' or '-' in Number!"));
                    
                    }

                    else if (!mSourceBuffer->IsDigit())
                        throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expected digit after 'e' or 'E' in Number!"));

                    while (true)
                    {
                        
                        while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                        if (mSourceBuffer->PeekChar() != '_') break;

                        buffer << mSourceBuffer->GetChar();

                        if (!mSourceBuffer->IsDigit())
                            throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                    }
                        
                }

                if (mSourceBuffer->PeekChar() == 'j' || mSourceBuffer->PeekChar() == 'J')
                {

                    buffer << mSourceBuffer->GetChar();
                
                }
                else if (nonZero)
                {

                    throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Unexpected digit found in Number!"));

                }

            }

        }
        else    /* Decimal */
        {

            if (mSourceBuffer->PeekChar() != '.')
            {

                while (true)
                {

                    while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                    if (mSourceBuffer->PeekChar() != '_') break;

                    buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsDigit())
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                }
            }

            if (mSourceBuffer->PeekChar() == '.')
            {

                buffer << mSourceBuffer->GetChar();

                while (true)
                {

                    while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                    if (mSourceBuffer->PeekChar() != '_') break;

                    buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsDigit())
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                }

            }

            if (mSourceBuffer->PeekChar() == 'e' || mSourceBuffer->PeekChar() == 'E')
            {

                buffer << mSourceBuffer->GetChar();

                if (mSourceBuffer->PeekChar() == '+' || mSourceBuffer->PeekChar() == '-')
                {

                    buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsDigit())
                        throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expected digit after '+' or '-' in Number!"));
                
                }

                else if (!mSourceBuffer->IsDigit())
                    throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expected digit after 'e' or 'E' in Number!"));

                while (true)
                {
                    
                    while (mSourceBuffer->IsDigit()) buffer << mSourceBuffer->GetChar();

                    if (mSourceBuffer->PeekChar() != '_') break;

                    buffer << mSourceBuffer->GetChar();

                    if (!mSourceBuffer->IsDigit())
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Expected digit after '_' in Number!"));

                }
                    
            }

            if (mSourceBuffer->PeekChar() == 'j' || mSourceBuffer->PeekChar() == 'J')
            {

                buffer << mSourceBuffer->GetChar();
            
            }

        }

        std::wstring key = buffer.str(); 

        mCurSymbol = std::make_shared<NumberToken>(
            mPosition,
            mSourceBuffer->BufferPosition(),
            std::make_shared<std::wstring>(key) );

        return;
    }


    /* Handle Operator and delimiters */
    switch (mSourceBuffer->GetChar())
    {
        case '(':

            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftParen);
            break;

        case '[':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftBracket);
            break;

        case '{':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftCurly);
            break;

        case ')':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightParen);
            break;

        case ']':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightBracket);
            break;

        case '}':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightCurly);
            break;

        case ';':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PySemiColon);
            break;

        case ',':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyComma);
            break;

        case '~':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyBitInvert);
            break;

        case '+':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyPlusAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyPlus);
            }
            break;

        case '-':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMinusAssign);
            }
            else if (mSourceBuffer->PeekChar() == '>')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyArrow);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMinus);
            }
            break;

        case '*':

            if (mSourceBuffer->PeekChar() == '*')
            {
                mSourceBuffer->Next();
                if (mSourceBuffer->PeekChar() == '=')
                {
                    mSourceBuffer->Next();
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyPowerAssign);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyPower);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMulAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMul);
            }
            break;   

        case '/':

            if (mSourceBuffer->PeekChar() == '/')
            {
                mSourceBuffer->Next();
                if (mSourceBuffer->PeekChar() == '=')
                {
                    mSourceBuffer->Next();
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyFloorDivAssign);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyFloorDiv);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyDivAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyDiv);
            }
            break;   

        case '<':

            if (mSourceBuffer->PeekChar() == '<')
            {
                mSourceBuffer->Next();
                if (mSourceBuffer->PeekChar() == '=')
                {
                    mSourceBuffer->Next();
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftLeftAssign);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftLeft);
                }
            }
            else if (mSourceBuffer->PeekChar() == '>')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyNotEqual);
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyLessEqual);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyLess);
            }
            break;   

        case '>':

            if (mSourceBuffer->PeekChar() == '>')
            {
                mSourceBuffer->Next();
                if (mSourceBuffer->PeekChar() == '=')
                {
                    mSourceBuffer->Next();
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftRightAssign);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftRight);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyGreaterEqual);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyGreater);
            }
            break;

        case '%':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyModuloAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyModulo);
            }
            break; 

        case '@':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMatriceAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMatrice);
            }
            break;

        case '&':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitAndAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitAnd);
            }
            break;

        case '|':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitOrAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitOr);
            }
            break;

        case '^':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitXorAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitXor);
            }
            break;

        case ':':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyColonAssign);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyColon);
            }
            break;

        case '=':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyEqual);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyAssign);
            }
            break;

        case '!':

            if (mSourceBuffer->PeekChar() != '=') 
                throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Expecting '!=' but found only '!' in source code!"));
            
            mSourceBuffer->Next();

            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyNotEqual);
            break;

        default:

            throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Found illegal character in source code!"));
            
            break;
    }

    /* Finally we check for matching parenthesis if any */
    if (    mCurSymbol->GetSymbolKind() == TokenKind::PyLeftParen ||
            mCurSymbol->GetSymbolKind() == TokenKind::PyLeftBracket ||
            mCurSymbol->GetSymbolKind() == TokenKind::PyLeftCurly)
            {
                mLevelStack.push( mCurSymbol->GetSymbolKind() );
            }

    else if (mCurSymbol->GetSymbolKind() == TokenKind::PyRightParen)
    {
        if (!mLevelStack.empty())
        {
            if (mLevelStack.top() == TokenKind::PyLeftParen)
            {
                mLevelStack.pop();
                return;
            }
        }

        throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Inconsistant ')' parenthesis matching!"));
            
    }

    else if (mCurSymbol->GetSymbolKind() == TokenKind::PyRightBracket)
    {
        if (!mLevelStack.empty())
        {
            if (mLevelStack.top() == TokenKind::PyLeftBracket)
            {
                mLevelStack.pop();
                return;
            }
        }

        throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Inconsistant ']' parenthesis matching!"));
            
    }

    else if (mCurSymbol->GetSymbolKind() == TokenKind::PyRightCurly)
    {
        if (!mLevelStack.empty())
        {
            if (mLevelStack.top() == TokenKind::PyLeftCurly)
            {
                mLevelStack.pop();
                return;
            }
        }

        throw std::make_shared<LexicalError>(
                                mSourceBuffer->BufferPosition(),
                                std::make_shared<std::wstring>(L"Inconsistant '}' parenthesis matching!"));
            
    }
}
