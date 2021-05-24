#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class FloorDivNode : public ExpressionNode
    {
        public:
            FloorDivNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        );
            std::shared_ptr<ExpressionNode> GetLeft();
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<ExpressionNode> GetRight();

        protected:
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
    };
}

