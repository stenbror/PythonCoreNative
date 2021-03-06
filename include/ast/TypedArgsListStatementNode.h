#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TypedArgsListStatementNode : public StatementNode
    {
        public:
            TypedArgsListStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<StatementNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<StatementNode> powerNode,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> typeComment
                        );

            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();
            std::shared_ptr<Token> GetSlash();
            std::shared_ptr<Token> GetMul();
            std::shared_ptr<StatementNode> GetMulNode();
            std::shared_ptr<Token> GetPower();
            std::shared_ptr<StatementNode> GetPowerNode();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetTypeComment();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mSlash;
            std::shared_ptr<Token> mMul;
            std::shared_ptr<StatementNode> mMulNode;
            std::shared_ptr<Token> mPower;
            std::shared_ptr<StatementNode> mPowerNode;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mTypeComment;
    };
}
