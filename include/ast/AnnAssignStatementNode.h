#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class AnnAssignStatementNode : public StatementNode
    {
        public:
            AnnAssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Node> next
                        );

            std::shared_ptr<Node> GetLeftNode();
            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<ExpressionNode> GetRightNode();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<Node> GetNextNode();

        protected:
            std::shared_ptr<Node> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Node> mNext;
            
    };
}
