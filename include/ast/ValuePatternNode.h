#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class ValuePatternNode : public StatementNode
    {
        public:
            ValuePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mDots;
            
    };
}
