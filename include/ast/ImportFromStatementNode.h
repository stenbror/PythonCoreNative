#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ImportFromStatementNode : public StatementNode
    {
        public:
            ImportFromStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op4
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetDots();
            std::shared_ptr<StatementNode> GetLeft();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<Token> GetOperator3();
            std::shared_ptr<StatementNode> GetRight();
            std::shared_ptr<Token> GetOperator4();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mDots;
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<StatementNode> mRight;
            std::shared_ptr<Token> mOp4;
    };
}
