#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ClassStatementNode : public StatementNode
    {
        public:
            ClassStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<Token> op5,
                            std::shared_ptr<StatementNode> right
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<Token> GetOperators3();
            std::shared_ptr<ExpressionNode> GetLeft();
            std::shared_ptr<Token> GetOperator4();
            std::shared_ptr<Token> GetOperator5();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp4;
            std::shared_ptr<Token> mOp5;
            std::shared_ptr<StatementNode> mRight;
    };
}
