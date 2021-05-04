#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class SubscriptNode : public ExpressionNode
    {
        public:
            SubscriptNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> next
                        );

        protected:
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mNext;
    };
}
