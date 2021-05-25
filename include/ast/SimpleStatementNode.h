#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class SimpleStatementNode : public StatementNode
    {
        public:
            SimpleStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> op1
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
