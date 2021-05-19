#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class GroupPatternNode : public StatementNode
    {
        public:
            GroupPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right,
                            std::shared_ptr<Token> op2
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<AST::StatementNode> mRight;
            std::shared_ptr<Token> mOp2;
            
    };
}