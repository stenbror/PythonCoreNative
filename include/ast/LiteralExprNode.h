#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>
#include <TokenKind.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class LiteralExprNode : public StatementNode
    {
        public:
            LiteralExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> mRight
                        );

            TokenKind LiteralExprType();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
            
    };
}
