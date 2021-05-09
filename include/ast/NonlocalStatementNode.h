#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class NonlocalStatementNode : public StatementNode
    {
        public:
            NonlocalStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
