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
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<NameToken> op3
                        );

        protected:
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<NameToken> mOp3;
    };
}
