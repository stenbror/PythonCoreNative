
#include <PythonCoreTokenizer.h>

using namespace PythonCoreNative::RunTime::Parser;
#include <iostream>

PythonCoreTokenizer::PythonCoreTokenizer(unsigned int tabSize, std::shared_ptr<SourceBuffer> sourceBuffer)
{
    if (sourceBuffer == nullptr) throw "No buffer!";

    mSourceBuffer = sourceBuffer;
    mPosition = mSourceBuffer->BufferPosition();
    mAtBOL = true;
    mPending = 0;
    
    
}

std::shared_ptr<Token> PythonCoreTokenizer::CurSymbol()
{
    return mCurSymbol;
}
            
unsigned int PythonCoreTokenizer::Position()
{
    return mSourceBuffer->BufferPosition();
}

void PythonCoreTokenizer::UnWindTokenStream(unsigned int pos)
{
    mSourceBuffer->SetPosition(pos);
}
            
void PythonCoreTokenizer::Advance()
{

    auto triviaList = std::make_shared<std::vector<std::shared_ptr<Trivia>>>();

    auto isUnicode = false, isFormated = false, isRaw = false;

_nextLine:  

    mIsBlankLine = false;

    isUnicode = isRaw = isFormated = false;

    /* Analyze start of source code line */
    if (mAtBOL)
    {

        mAtBOL = false;
        unsigned int col = 0;

        while (mSourceBuffer->PeekChar() == ' ' || mSourceBuffer->PeekChar() == '\v' || mSourceBuffer->PeekChar() == '\t')
        {
            auto startPos = mSourceBuffer->BufferPosition();

            switch (mSourceBuffer->PeekChar())
            {
                case ' ':
                    {
                        
                        while (mSourceBuffer->PeekChar() == ' ')
                        {

                            mSourceBuffer->Next();
                            col++;

                        }

                    }

                    triviaList->push_back( std::make_shared<WhiteSpaceTrivia>(startPos, mSourceBuffer->BufferPosition(), L' ') );
                    break;
                case '\t':
                    
                    col = (col / mTabSize + 1) * mTabSize;
                    mSourceBuffer->Next();
                    triviaList->push_back( std::make_shared<WhiteSpaceTrivia>(startPos, mSourceBuffer->BufferPosition(), L'\t') );
                    break;

                case '\v':
                    
                    col = 0;
                    mSourceBuffer->Next();
                    triviaList->push_back( std::make_shared<WhiteSpaceTrivia>(startPos, mSourceBuffer->BufferPosition(), L'\v') );
                    break;
            }

        }

        if (    mSourceBuffer->PeekChar() == '#' || 
                mSourceBuffer->PeekChar() == '\r' || 
                mSourceBuffer->PeekChar() == '\n' || 
                mSourceBuffer->PeekChar() == '\\')
        {

            if (col == 0 && (mSourceBuffer->PeekChar() == '\r' || mSourceBuffer->PeekChar() == '\n') && mIsBlankLine)
                mIsBlankLine = false;

            else if (mIsInteractive)
            {

                col = 0;
                mIsBlankLine = false;

            }
            else mIsBlankLine = true;

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
    {   std::wcout << L" Pending: " << mPending << L" " << std::endl;

        if (mPending < 0)
        {
            mPending++;

            mCurSymbol = std::make_shared<Token>(
                mPosition,
                mSourceBuffer->BufferPosition(),
                TokenKind::Dedent,
                triviaList);
        }
        else
        {

            mPending--;

            mCurSymbol = std::make_shared<Token>(
                mPosition,
                mSourceBuffer->BufferPosition(),
                TokenKind::Indent,
                triviaList);

        }

        return;

    }

_again:

    mPosition = mSourceBuffer->BufferPosition();

    /* Handle whitespace and other trivia */
    while (mSourceBuffer->PeekChar() == ' ' || mSourceBuffer->PeekChar() == '\v' || mSourceBuffer->PeekChar() == '\t')
    {
        auto ch = mSourceBuffer->GetChar();
        switch (ch)
        {
            case ' ':

                while (mSourceBuffer->PeekChar() == ' ')
                {
                    mSourceBuffer->Next();
                }

                triviaList->push_back( std::make_shared<WhiteSpaceTrivia>(mPosition, mSourceBuffer->BufferPosition(), ch) );
                break;

            case '\t':

                triviaList->push_back( std::make_shared<WhiteSpaceTrivia>(mPosition, mSourceBuffer->BufferPosition(), ch) );
                break;

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
                std::make_shared<std::wstring>(key),
                triviaList);

            return ;
        }

        triviaList->push_back( std::make_shared<CommentTrivia>(mPosition, mSourceBuffer->BufferPosition(), std::make_shared<std::wstring>(key)) );

        goto _again;
    }


    /* Handle End of File */
    if (mSourceBuffer->PeekChar() == '\0')
    {
        // Add check for interactive mode later!

        mCurSymbol = std::make_shared<Token>(   
            mPosition,
            mSourceBuffer->BufferPosition(),
            TokenKind::EndOfFile,
            triviaList);

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
            mCurSymbol = std::make_shared<Token>(mPosition, mSourceBuffer->BufferPosition(), mReservedKeywords.at(key), triviaList);
            
            return ;
        }

        /* Analyze string prefix */
        else if (key.size() < 3 && ( mSourceBuffer->PeekChar() == '"' || mSourceBuffer->PeekChar() == '\'') )
        {

            if (key.find_first_of(L"r", 0, sizeof(wchar_t)))
            {
                isRaw = true;
            }

            else if (key.find_first_of(L"u", 0, sizeof(wchar_t)))
            {
                isUnicode = true;
            }

            else if (key.find_first_of(L"R", 0, sizeof(wchar_t)))
            {
                isRaw = true;
            }

            else if (key.find_first_of(L"U", 0, sizeof(wchar_t)))
            {
                isUnicode = true;
            }

            else if (key.find_first_of(L"f", 0, sizeof(wchar_t)))
            {
                isFormated = true;
            }

            else if (key.find_first_of(L"F", 0, sizeof(wchar_t)))
            {
                isFormated = true;
            }

            else if (key.find_first_of(L"fr", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else if (key.find_first_of(L"FR", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else if (key.find_first_of(L"rf", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else if (key.find_first_of(L"rF", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else if (key.find_first_of(L"Rf", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else if (key.find_first_of(L"RF", 0, sizeof(wchar_t)))
            {
                isFormated = isRaw = true;
            }

            else
            {

                throw std::make_shared<LexicalError>(   
                    mPosition, 
                    std::make_shared<std::wstring>(L"Illegal prefix for string!"));
            
            }

            goto _letterQuote;
        }
        else
        {

            mCurSymbol = std::make_shared<NameToken>(
                mPosition, 
                mSourceBuffer->BufferPosition(), 
                std::make_shared<std::wstring>(key),
                triviaList);
            
            return;

        }
    }


    /* Handle Newline as Token or trivia */
    if (mSourceBuffer->PeekChar() == '\r' || mSourceBuffer->PeekChar() == '\n')
    {
        mAtBOL = true;
        auto startPos = mSourceBuffer->BufferPosition();

        wchar_t ch1 = mSourceBuffer->PeekChar() == '\r' ? mSourceBuffer->GetChar() : ' ', 
                ch2 = mSourceBuffer->PeekChar() == '\n' ? mSourceBuffer->GetChar() : ' ';

        if (mSourceBuffer->PeekChar() != '\0' && (mIsBlankLine || !mLevelStack.empty()))
        {
            
            triviaList->push_back( std::make_shared<NewLineTrivia>(startPos, mSourceBuffer->BufferPosition(), ch1, ch2) );

            goto _nextLine;
        }

        mCurSymbol = std::make_shared<Token>(
            mPosition,
            mSourceBuffer->BufferPosition(),
            TokenKind::Newline,
            triviaList);

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
                    TokenKind::PyElipsis,
                    triviaList);

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
                    TokenKind::PyDot,
                    triviaList);

                return;
        }

        mSourceBuffer->UngetChar(L'.');
    }


    /* Handle numbers */
    if (mSourceBuffer->IsDigit() || mSourceBuffer->PeekChar() == '.')
    {
        bool isImaginary = false, isReal = false;

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
                    
                    isReal = true;

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

                    isReal = true;

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

                    isImaginary = true;

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

                isReal = true;

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

                isReal = true;

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

                isImaginary = true;

                buffer << mSourceBuffer->GetChar();
            
            }

        }

        std::wstring key = buffer.str(); 

        mCurSymbol = std::make_shared<NumberToken>(
            mPosition,
            isImaginary,
            isReal,
            mSourceBuffer->BufferPosition(),
            std::make_shared<std::wstring>(key),
            triviaList );

        return;
    }


_letterQuote:

    /* String handling */
    if (mSourceBuffer->PeekChar() == '\'' || mSourceBuffer->PeekChar() == '"')
    {

        mPosition = mSourceBuffer->BufferPosition();

        std::wstringstream buffer;

        auto quote = mSourceBuffer->GetChar();
        auto quoteSize = 1;
        auto quoteEndSize = 0;

        if (mSourceBuffer->PeekChar() == quote)
        {

            mSourceBuffer->Next();

            if (mSourceBuffer->PeekChar() == quote)
            {

                quoteSize = 3;
                mSourceBuffer->Next();
            
            }
            else quoteEndSize = 1;

        }
        else mSourceBuffer->UngetChar(quote);

        while (quoteSize != quoteEndSize)
        {

            switch (mSourceBuffer->PeekChar())
            {
                case '\0':

                    if (!mIsInteractive)
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Unterminated string in non interactive mode!") );

                    throw ; // Ask for more input....
                    
                case '\r':
                case '\n':

                    if (quoteSize == 1)
                        throw std::make_shared<LexicalError>(
                            mSourceBuffer->BufferPosition(),
                            std::make_shared<std::wstring>(L"Found newline inside sinqle quote string!") );

                    if (mSourceBuffer->PeekChar() == '\r')
                    {

                        buffer << mSourceBuffer->GetChar();

                    }

                    if (mSourceBuffer->PeekChar() == '\n')
                    {

                        buffer << mSourceBuffer->GetChar();
                        
                    }
                    break;

                default:

                    if (quote == mSourceBuffer->PeekChar())
                    {

                        quoteEndSize++;
                        buffer << mSourceBuffer->GetChar();

                    }
                    else
                    {

                        quoteEndSize = 0;

                        if (mSourceBuffer->PeekChar() == '\\')
                        {

                            buffer << mSourceBuffer->GetChar();

                            if (mSourceBuffer->PeekChar() == '\r')
                            {

                                buffer << mSourceBuffer->GetChar();

                            }

                            if (mSourceBuffer->PeekChar() == '\n')
                            {

                                buffer << mSourceBuffer->GetChar();
                                
                            }

                        }
                        else
                        {

                            buffer << mSourceBuffer->GetChar();

                        }

                    }

                    break;
            }

        }

        std::wstring key = buffer.str(); 

        mCurSymbol = std::make_shared<StringToken>(
            mPosition,
            mSourceBuffer->BufferPosition(),
            std::make_shared<std::wstring>(key),
            isRaw,
            isUnicode,
            isFormated,
            triviaList );

        return;

    }


    /* Handle line continuation */
    if (mSourceBuffer->PeekChar() == '\\')
    {

        mSourceBuffer->Next();
        
        triviaList->push_back( std::make_shared<LineContinuationTrivia>(mSourceBuffer->BufferPosition() - 1, mSourceBuffer->BufferPosition()) );

        if (mSourceBuffer->PeekChar() == '\r' || mSourceBuffer->PeekChar() == '\n')
        {
            unsigned int start = mSourceBuffer->BufferPosition();

            wchar_t ch1 = mSourceBuffer->PeekChar() == '\r' ? mSourceBuffer->GetChar() : ' ';
            wchar_t ch2 = mSourceBuffer->PeekChar() == '\n' ? mSourceBuffer->GetChar() : ' ';

            triviaList->push_back( std::make_shared<NewLineTrivia>(start, mSourceBuffer->BufferPosition(), ch1, ch2) );

            goto _again;

        }
        
        throw std::make_shared<LexicalError>(
            mSourceBuffer->BufferPosition(),
            std::make_shared<std::wstring>(L"Line shift must follow line continuation '\'")
        );

    }


    /* Handle Operator and delimiters */
    switch (mSourceBuffer->GetChar())
    {
        case '(':

            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftParen,
                                                    triviaList);
            break;

        case '[':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftBracket,
                                                    triviaList);
            break;

        case '{':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyLeftCurly,
                                                    triviaList);
            break;

        case ')':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightParen,
                                                    triviaList);
            break;

        case ']':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightBracket,
                                                    triviaList);
            break;

        case '}':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyRightCurly,
                                                    triviaList);
            break;

        case ';':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PySemiColon,
                                                    triviaList);
            break;

        case ',':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyComma,
                                                    triviaList);
            break;

        case '~':
        
            mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                    mSourceBuffer->BufferPosition(),
                                                    TokenKind::PyBitInvert,
                                                    triviaList);
            break;

        case '+':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyPlusAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyPlus,
                                                        triviaList);
            }
            break;

        case '-':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMinusAssign,
                                                        triviaList);
            }
            else if (mSourceBuffer->PeekChar() == '>')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyArrow,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMinus,
                                                        triviaList);
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
                                                            TokenKind::PyPowerAssign,
                                                            triviaList);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyPower,
                                                            triviaList);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMulAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMul,
                                                        triviaList);
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
                                                            TokenKind::PyFloorDivAssign,
                                                            triviaList);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyFloorDiv,
                                                            triviaList);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyDivAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyDiv,
                                                        triviaList);
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
                                                            TokenKind::PyShiftLeftAssign,
                                                            triviaList);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftLeft,
                                                            triviaList);
                }
            }
            else if (mSourceBuffer->PeekChar() == '>')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyNotEqual,
                                                        triviaList);
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyLessEqual,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyLess,
                                                        triviaList);
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
                                                            TokenKind::PyShiftRightAssign,
                                                            triviaList);
                }
                else
                {
                    mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                            mSourceBuffer->BufferPosition(),
                                                            TokenKind::PyShiftRight,
                                                            triviaList);
                }
            }
            else if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyGreaterEqual,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyGreater,
                                                        triviaList);
            }
            break;

        case '%':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyModuloAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyModulo,
                                                        triviaList);
            }
            break; 

        case '@':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMatriceAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyMatrice,
                                                        triviaList);
            }
            break;

        case '&':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitAndAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitAnd,
                                                        triviaList);
            }
            break;

        case '|':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitOrAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitOr,
                                                        triviaList);
            }
            break;

        case '^':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitXorAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyBitXor,
                                                        triviaList);
            }
            break;

        case ':':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyColonAssign,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyColon,
                                                        triviaList);
            }
            break;

        case '=':

            if (mSourceBuffer->PeekChar() == '=')
            {
                mSourceBuffer->Next();
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyEqual,
                                                        triviaList);
            }
            else
            {
                mCurSymbol = std::make_shared<Token>(   mPosition, 
                                                        mSourceBuffer->BufferPosition(),
                                                        TokenKind::PyAssign,
                                                        triviaList);
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
                                                    TokenKind::PyNotEqual,
                                                    triviaList);
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
