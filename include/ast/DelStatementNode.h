#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DelStatementNode : public StatementNode
    {
        public:
            DelStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        );
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<ExpressionNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            
    };
}
