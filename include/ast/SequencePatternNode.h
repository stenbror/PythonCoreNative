#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class SequencePatternNode : public StatementNode
    {
        public:
            SequencePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> right,
                            std::shared_ptr<Token> op2
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<AST::StatementNode> GetRight();
            std::shared_ptr<Token> GetOperator2();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<AST::StatementNode> mRight;
            std::shared_ptr<Token> mOp2;
            
    };
}
