#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class ExceptNode : public StatementNode
    {
        public:
            ExceptNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
    };
}

