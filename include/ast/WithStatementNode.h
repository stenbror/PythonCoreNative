#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class WithStatementNode : public StatementNode
    {
        public:
            WithStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> openParenthesis,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> withItems,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> closeParenthesis,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<Token> GetOpenParenthesis();
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> GetWithItems();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();
            std::shared_ptr<Token> GetCloseParenthesis();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<Token> GetOperator3();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOpenParenthesis;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mWithItems;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mCloseParenthesis;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<StatementNode> mRight;
    };
}
