#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ImportStatementNode : public StatementNode
    {
        public:
            ImportStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
    };
}
