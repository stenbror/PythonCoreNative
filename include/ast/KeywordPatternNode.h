#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class KeywordPatternNode : public StatementNode
    {
        public:
            KeywordPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<AST::StatementNode> right
                        );

            std::shared_ptr<NameToken> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<AST::StatementNode> GetRight();

        protected:
            std::shared_ptr<NameToken> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<AST::StatementNode> mRight;
    };
}
