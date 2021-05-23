#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DictionaryContainerNode : public ExpressionNode
    {
        public:
            DictionaryContainerNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> entries,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> GetEntries();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> mEntries;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
