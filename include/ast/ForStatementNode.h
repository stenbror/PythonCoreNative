#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ForStatementNode : public StatementNode
    {
        public:
            ForStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> next,
                            std::shared_ptr<StatementNode> extra
                        );
            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<ExpressionNode> GetLeft();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<ExpressionNode> GetRight();
            std::shared_ptr<Token> GetOperator3();
            std::shared_ptr<Token> GetOperator4();
            std::shared_ptr<StatementNode> GetNext();
            std::shared_ptr<StatementNode> GetExtra();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<Token> mOp4;
            std::shared_ptr<StatementNode> mNext;
            std::shared_ptr<StatementNode> mExtra;
    };
}
