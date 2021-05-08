#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DecoratorsStatementNode : public StatementNode
    {
        public:
            DecoratorsStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
    };
}
