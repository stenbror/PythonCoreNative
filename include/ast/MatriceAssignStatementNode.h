#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class MatriceAssignStatementNode : public StatementNode
    {
        public:
            MatriceAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right
                        );

            std::shared_ptr<Node> GetLeft();
            std::shared_ptr<Token> GetOperartor();
            std::shared_ptr<ExpressionNode> GetRight();

        protected:
            std::shared_ptr<Node> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            
    };
}
