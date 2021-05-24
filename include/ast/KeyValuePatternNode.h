#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class KeyValuePatternNode : public StatementNode
    {
        public:
            KeyValuePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<AST::StatementNode> key,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<AST::StatementNode> value
                        );

            std::shared_ptr<AST::StatementNode> GetKey();
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<AST::StatementNode> GetValue();

        protected:
            std::shared_ptr<AST::StatementNode> mKey;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<AST::StatementNode> mValue;
            
    };
}
