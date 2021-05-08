#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DecoratorStatementNode : public StatementNode
    {
        public:
            DecoratorStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<Token> mOp4;
    };
}
