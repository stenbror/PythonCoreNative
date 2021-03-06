#pragma once

#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class FileInputNode : public StatementNode
    {
        public:
            FileInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> eof
                        );
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetNewlines();
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> GetNodes();
            std::shared_ptr<Token> GetEof();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mNewlines;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
            std::shared_ptr<Token> mEof;
    };
}
