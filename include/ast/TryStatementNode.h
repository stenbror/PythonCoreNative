#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TryStatementNode : public StatementNode
    {
        public:
            TryStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> exceptNodes,
                            std::shared_ptr<StatementNode> elseNode,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mExceptNodes; 
            std::shared_ptr<StatementNode> mElseNode;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<Token> mOp4;
            std::shared_ptr<StatementNode> mRight;
    };
}
