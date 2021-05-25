#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class StarPatternNode : public StatementNode
    {
        public:
            StarPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right
                        );

            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<AST::StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<AST::StatementNode> mRight;
            
    };
}
