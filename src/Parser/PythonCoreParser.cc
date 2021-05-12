
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

PythonCoreParser::PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer)
{
    mLexer = lexer;
    mFlowLevel = 0;
    mFuncLevel = 0;
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseEvalInput()
{
    mLexer->Advance();
    auto startPos = mLexer->Position();
    auto newlines = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    auto right = ParseTestList();

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
    {
        newlines->push_back( mLexer->CurSymbol() );
        mLexer->Advance();
    }

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::EndOfFile )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting End of File in Func!"));

    return std::make_shared<AST::EvalInputNode>(startPos, mLexer->Position(), newlines, right, mLexer->CurSymbol());
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseFileInput()
{
    mLexer->Advance();
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::StatementNode>>>();
    auto newlines = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    while ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::EndOfFile )
    {
        if ( mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline )
        {
            newlines->push_back( mLexer->CurSymbol() );
            mLexer->Advance();
        }
        else
            nodes->push_back( ParseStmt() );
    }

    return std::make_shared<AST::FileInputNode>(startPos, mLexer->Position(), newlines, nodes, mLexer->CurSymbol());
}

std::shared_ptr<AST::StatementNode> PythonCoreParser::ParseSingleInput()
{
    return nullptr;
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncTypeInput()
{
    mLexer->Advance();
    auto startPos = mLexer->Position();
    auto newlines = std::make_shared<std::vector<std::shared_ptr<Token>>>();

    auto right = ParseFuncType();

    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::Newline)
    {
        newlines->push_back( mLexer->CurSymbol() );
        mLexer->Advance();
    }

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::EndOfFile )
        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting End of File in Func!"));


    return std::make_shared<AST::TypeInputNode>(startPos, mLexer->Position(), newlines, right, mLexer->CurSymbol());
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseFuncType()
{
    auto startPos = mLexer->Position();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyLeftParen )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting '(' in Func!"));

    auto symbol1 = mLexer->CurSymbol();
    mLexer->Advance();

    auto left = mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyRightParen ? nullptr : ParseTypeList();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyRightParen )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting ')' in Func!"));

    auto symbol2 = mLexer->CurSymbol();
    mLexer->Advance();

    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyArrow )
            throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Expecting '->' in Func!"));

    auto symbol3 = mLexer->CurSymbol();
    mLexer->Advance();

    auto right = ParseTest();

    return std::make_shared<AST::FuncTypeNode>(startPos, mLexer->Position(), symbol1, left, symbol2, symbol3, right);
}

std::shared_ptr<AST::TypeNode> PythonCoreParser::ParseTypeList()
{
    auto startPos = mLexer->Position();
    auto nodes = std::make_shared<std::vector<std::shared_ptr<AST::ExpressionNode>>>();
    auto separators = std::make_shared<std::vector<std::shared_ptr<Token>>>();
    std::shared_ptr<Token> mulOp = nullptr, powerOp = nullptr;
    std::shared_ptr<AST::ExpressionNode> mulNode = nullptr, powerNode = nullptr;

    switch (mLexer->CurSymbol()->GetSymbolKind())
    {
        case TokenKind::PyMul:

            mulOp = mLexer->CurSymbol();
            mLexer->Advance();

            mulNode = ParseTest();

            while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
            {
                separators->push_back( mLexer->CurSymbol() );
                mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyPower) nodes->push_back( ParseTest() );
                else
                {
                    powerOp = mLexer->CurSymbol();
                    mLexer->Advance();

                    powerNode = ParseTest();


                    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma )
                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Unexpected ',' after '**' argument!"));

                }
            }

            break;

        case TokenKind::PyPower:

            powerOp = mLexer->CurSymbol();
            mLexer->Advance();

            powerNode = ParseTest();

            break;

        default:

            nodes->push_back( ParseTest() );

            while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
            {
                separators->push_back( mLexer->CurSymbol() );
                mLexer->Advance();

                if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyPower)
                {
                    powerOp = mLexer->CurSymbol();
                    mLexer->Advance();

                    powerNode = ParseTest();

                    if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma )
                        throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Unexpected ',' after '**' argument!"));

                }
                else if (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyMul)
                {
                    mulOp = mLexer->CurSymbol();
                    mLexer->Advance();

                    mulNode = ParseTest();

                    while (mLexer->CurSymbol()->GetSymbolKind() == TokenKind::PyComma)
                    {
                        separators->push_back( mLexer->CurSymbol() );
                        mLexer->Advance();

                        if (mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyPower) nodes->push_back( ParseTest() );
                        else
                        {
                            powerOp = mLexer->CurSymbol();
                            mLexer->Advance();

                            powerNode = ParseTest();


                            if ( mLexer->CurSymbol()->GetSymbolKind() != TokenKind::PyComma )
                                throw std::make_shared<SyntaxError>(mLexer->Position(), mLexer->CurSymbol(), std::make_shared<std::basic_string<char32_t>>(U"Unexpected ',' after '**' argument!"));

                        }
                    }
                }
                else nodes->push_back( ParseTest() );
            }

            break;
    }

    return std::make_shared<AST::TypeListNode>(startPos, mLexer->Position(), nodes, separators, mulOp, mulNode, powerOp, powerNode);
}