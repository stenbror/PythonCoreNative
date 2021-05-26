#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class VarArgsListExpressionNode : public ExpressionNode
    {
        public:
            VarArgsListExpressionNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<NameToken> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<NameToken> powerNode
                        );

            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();
            std::shared_ptr<Token> GetSlash();
            std::shared_ptr<Token> GetMul();
            std::shared_ptr<NameToken> GetMulNode();
            std::shared_ptr<Token> GetPower();
            std::shared_ptr<NameToken> GetPowerNode();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mSlash;
            std::shared_ptr<Token> mMul;
            std::shared_ptr<NameToken> mMulNode;
            std::shared_ptr<Token> mPower;
            std::shared_ptr<NameToken> mPowerNode;
    };
}
