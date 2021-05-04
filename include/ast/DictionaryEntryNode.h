#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class DictionaryEntryNode : public ExpressionNode
    {
        public:
            DictionaryEntryNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<ExpressionNode> key,
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> value
                        );

        protected:
            std::shared_ptr<ExpressionNode> mKey;
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mValue;
    };
}

