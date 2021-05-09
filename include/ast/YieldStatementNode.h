#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class YieldStatementNode : public StatementNode
    {
        public:
            YieldStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> right
                        );

        protected:
            std::shared_ptr<ExpressionNode> mRight;
    };
}
