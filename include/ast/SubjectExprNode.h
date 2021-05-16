#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class SubjectExprNode : public StatementNode
    {
        public:
            SubjectExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> right
                        );

        protected:
            std::shared_ptr<ExpressionNode> mRight;
            
    };
}
