#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class VFPDefAssignExpressionNode : public ExpressionNode
    {
        public:
            VFPDefAssignExpressionNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right
                        );

            std::shared_ptr<NameToken> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<ExpressionNode> getRight();

        protected:
            std::shared_ptr<NameToken> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
    };
}
