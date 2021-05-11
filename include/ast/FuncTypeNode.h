#pragma once

#include <ast/TypeNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class FuncTypeNode : public TypeNode
    {
        public:
            FuncTypeNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<TypeNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> right
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<TypeNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<ExpressionNode> mRight;
    };
}
