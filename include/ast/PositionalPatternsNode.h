#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class PositionalPatternsNode : public StatementNode
    {
        public:
            PositionalPatternsNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
