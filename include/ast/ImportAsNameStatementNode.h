#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ImportAsNameStatementNode : public StatementNode
    {
        public:
            ImportAsNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<Token> op3
                        );

            std::shared_ptr<Token> GetOperator1();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<Token> GetOperator3();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
    };
}
