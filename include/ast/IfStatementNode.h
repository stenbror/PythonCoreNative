#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class IfStatementNode : public StatementNode
    {
        public:
            IfStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<StatementNode> next
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<ExpressionNode> GetLeft();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<StatementNode> GetRight();
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> GetElifNodes();
            std::shared_ptr<StatementNode> GetGetElseNode();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<StatementNode> mRight;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes; // 'elif' statements
            std::shared_ptr<StatementNode> mNext; // 'else' statement
    };
}
