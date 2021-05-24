#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class GlobalStatementNode : public StatementNode
    {
        public:
            GlobalStatementNode(  
                            unsigned int start, unsigned int end,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );

            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
