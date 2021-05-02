
#include <PythonCoreParser.h>

using namespace PythonCoreNative::RunTime::Parser;

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseAtom()
{
    auto startPos = mLexer->Position();
    auto curSymbol = mLexer->CurSymbol();

    switch (curSymbol->GetSymbolKind())
    {
        case TokenKind::PyFalse:
            mLexer->Advance();
            return std::make_shared<AST::AtomFalseNode>(startPos, mLexer->Position(), curSymbol);
        case TokenKind::PyTrue:
            mLexer->Advance();
            return std::make_shared<AST::AtomTrueNode>(startPos, mLexer->Position(), curSymbol);
        case TokenKind::PyNone:
            mLexer->Advance();
            return std::make_shared<AST::AtomNoneNode>(startPos, mLexer->Position(), curSymbol);
        case TokenKind::PyElipsis:
            mLexer->Advance();
            return std::make_shared<AST::AtomElipsisNode>(startPos, mLexer->Position(), curSymbol);
        case TokenKind::Name:
            mLexer->Advance();
            return std::make_shared<AST::AtomNameNode>(startPos, mLexer->Position(), std::static_pointer_cast<NameToken>(curSymbol));
        case TokenKind::Number:
            mLexer->Advance();
            return std::make_shared<AST::AtomNumberNode>(startPos, mLexer->Position(), std::static_pointer_cast<NumberToken>(curSymbol));
        case TokenKind::String:
            {
                auto lst = std::make_shared<std::vector<std::shared_ptr<StringToken>>>();
                while (curSymbol->GetSymbolKind() == TokenKind::String)
                {
                    lst->push_back(std::static_pointer_cast<StringToken>(curSymbol));
                    mLexer->Advance();
                    curSymbol = mLexer->CurSymbol();
                }
                return std::make_shared<AST::AtomStringNode>(startPos, mLexer->Position(), lst);
            }

        default:
            throw ;
    }
    
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseAtomExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParsePower()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseFactor()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTerm()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseArith()
{
    return nullptr;
}


std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseShift()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseAndExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseXorExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseOrExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseStarExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseComparison()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseNotTest()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseAndTest()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseOrTest()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseLambda(bool isCond)
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTestNoCond()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTest()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseNamedExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTestListComp()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTrailer()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseSubscriptList()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseSubscript()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseExprList()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseTestList()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseDictorSetMaker()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseArgList()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseArgument()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseCompIter()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseSyncCompFor()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseCompFor()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseCompIf()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseYieldExpr()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseVarArgsList()
{
    return nullptr;
}

std::shared_ptr<AST::ExpressionNode> PythonCoreParser::ParseVFPAssign()
{
    return nullptr;
}
