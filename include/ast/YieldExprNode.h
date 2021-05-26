#pragma once

#include <ast/ExpressionNode.h>
#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class YieldExprNode : public ExpressionNode
    {
        public:
            YieldExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        );

            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
    };
}
