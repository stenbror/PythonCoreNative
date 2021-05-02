#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class MatriceNode : public ExpressionNode
    {
        public:
            MatriceNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        );

        protected:
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
    };
}

