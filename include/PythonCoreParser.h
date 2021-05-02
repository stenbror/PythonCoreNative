#pragma once

#include <PythonCoreTokenizer.h>

#include <ast/ExpressionNode.h>
#include <ast/StatementNode.h>


#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreParser
    {
        public:
            PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer);

        protected:
            std::shared_ptr<AST::ExpressionNode> ParseAtom();
            std::shared_ptr<AST::ExpressionNode> ParseAtomExpr();
            std::shared_ptr<AST::ExpressionNode> ParsePower();
            std::shared_ptr<AST::ExpressionNode> ParseFactor();
            std::shared_ptr<AST::ExpressionNode> ParseTerm();
            std::shared_ptr<AST::ExpressionNode> ParseArith();
            std::shared_ptr<AST::ExpressionNode> ParseShift();
            std::shared_ptr<AST::ExpressionNode> ParseAndExpr();
            std::shared_ptr<AST::ExpressionNode> ParseXorExpr();
            std::shared_ptr<AST::ExpressionNode> ParseOrExpr();
            std::shared_ptr<AST::ExpressionNode> ParseStarExpr();
            std::shared_ptr<AST::ExpressionNode> ParseComparison();
            std::shared_ptr<AST::ExpressionNode> ParseNotTest();
            std::shared_ptr<AST::ExpressionNode> ParseAndTest();
            std::shared_ptr<AST::ExpressionNode> ParseOrTest();
            std::shared_ptr<AST::ExpressionNode> ParseLambda(bool isCond);
            std::shared_ptr<AST::ExpressionNode> ParseTestNoCond();
            std::shared_ptr<AST::ExpressionNode> ParseTest();
            std::shared_ptr<AST::ExpressionNode> ParseNamedExpr();

        protected:
            std::shared_ptr<PythonCoreTokenizer> mLexer;
    };
}
