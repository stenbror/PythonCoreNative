#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class ComplexNumberNode : public StatementNode
    {
        public:
            ComplexNumberNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NumberToken> real,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NumberToken> imaginary
                        );

        protected:
            std::shared_ptr<Token> mRealSign;
            std::shared_ptr<NumberToken> mReal;
            std::shared_ptr<Token> mImaginarySign;
            std::shared_ptr<NumberToken> mImaginary;
            
    };
}
