#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class WildCardPatternNode : public StatementNode
    {
        public:
            WildCardPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            
    };
}
