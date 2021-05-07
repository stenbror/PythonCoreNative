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
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> withItems,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mWithItems;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<StatementNode> mRight;
    };
}
