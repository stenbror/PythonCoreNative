#pragma once

#include <ast/TypeNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class TypeInputNode : public TypeNode
    {
        public:
            TypeInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<TypeNode> right,
                            std::shared_ptr<Token> eof
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mNewlines;
            std::shared_ptr<TypeNode> mRight;
            std::shared_ptr<Token> mEof;
    };
}
