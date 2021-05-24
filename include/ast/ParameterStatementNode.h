#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ParameterStatementNode : public StatementNode
    {
        public:
            ParameterStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op2
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<StatementNode> mRight;
    };
}
