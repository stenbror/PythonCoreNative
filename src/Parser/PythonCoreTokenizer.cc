
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





    /* Handle Opetator and delimiters */
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
                throw ;
            
            mSourceBuffer->Next();

            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyNotEqual);
            break;

        default:

            throw ;
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

        throw ;
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

        throw ;
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

        throw ;
    }
}
