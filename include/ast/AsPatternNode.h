#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AsPatternNode : public StatementNode
    {
        public:
            AsPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                            
                        );

            std::shared_ptr<StatementNode> GetLeft();
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
            
    };
}
