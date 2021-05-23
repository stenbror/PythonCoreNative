#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class CompareInNode : public ExpressionNode
    {
        public:
            CompareInNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        );
            std::shared_ptr<ExpressionNode>  GetLeft();
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<ExpressionNode> GetRight();

        protected:
            std::shared_ptr<ExpressionNode>  mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
    };
}

