#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class CompIfNode : public ExpressionNode
    {
        public:
            CompIfNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<ExpressionNode> next
                        );
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<ExpressionNode> GetRight();
            std::shared_ptr<ExpressionNode> GetNext();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<ExpressionNode> mNext;
    };
}
