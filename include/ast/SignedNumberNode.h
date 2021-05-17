#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class SignedNumberNode : public StatementNode
    {
        public:
            SignedNumberNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NumberToken> number
                        );

        protected:
            std::shared_ptr<Token> mSign;
            std::shared_ptr<NumberToken> mNumber;
            
    };
}
