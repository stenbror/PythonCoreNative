#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class MatchStatementNode : public StatementNode
    {
        public:
            MatchStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> op5
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<Token> mOp4;
            std::shared_ptr<Token> mOp5;
            std::shared_ptr<AST::StatementNode> mLeft;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
    };
}
