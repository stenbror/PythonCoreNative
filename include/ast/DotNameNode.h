#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DotNameNode : public ExpressionNode
    {
        public:
            DotNameNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NameToken> op2
                        );
            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<NameToken> GetOperator2();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<NameToken> mOp2;
    };
}
