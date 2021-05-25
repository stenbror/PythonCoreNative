#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TestNode : public ExpressionNode
    {
        public:
            TestNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> Next
                        );

            std::shared_ptr<ExpressionNode> GetLeft();
            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<ExpressionNode> GetRight();
            std::shared_ptr<ExpressionNode> GetNext();

        protected:
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<ExpressionNode> mNext;
    };
}
