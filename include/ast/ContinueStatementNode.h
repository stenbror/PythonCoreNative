#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ContinueStatementNode : public StatementNode
    {
        public:
            ContinueStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        );
             std::shared_ptr<Token> GetOperator();

        protected:
            std::shared_ptr<Token> mOp1;
    };
}
