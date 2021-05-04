#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class SetContainerNode : public ExpressionNode
    {
        public:
            SetContainerNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> entries,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> mEntries;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
    };
}
