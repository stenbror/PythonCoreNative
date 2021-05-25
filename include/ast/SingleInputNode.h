#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class SingleInputNode : public StatementNode
    {
        public:
            SingleInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> newline,
                            std::shared_ptr<StatementNode> right
                        );

            std::shared_ptr<Token> GetNewline();
            std::shared_ptr<StatementNode> GetRight();

        protected:
            std::shared_ptr<Token> mNewline;
            std::shared_ptr<StatementNode> mRight;
    };
}
