#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DottedAsNameStatementNode : public StatementNode
    {
        public:
            DottedAsNameStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<NameToken> op2
                        );
            std::shared_ptr<StatementNode> GetLeft();
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<NameToken> GetOperator2();

        protected:
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<NameToken> mOp2;
    };
}
