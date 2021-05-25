#pragma once

#include <ast/TypeNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TypeListNode : public TypeNode
    {
        public:
            TypeListNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<ExpressionNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<ExpressionNode> powerNode
                        );

            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();
            std::shared_ptr<Token> GetMul();
            std::shared_ptr<ExpressionNode> GetMulNode();
            std::shared_ptr<Token> GetPower();
            std::shared_ptr<ExpressionNode> GetPowerNode();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mMul;
            std::shared_ptr<ExpressionNode> mMulNode;
            std::shared_ptr<Token> mPower;
            std::shared_ptr<ExpressionNode> mPowerNode;
    };
}
