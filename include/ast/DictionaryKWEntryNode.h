#pragma once

#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class DictionaryKWEntryNode : public ExpressionNode
    {
        public:
            DictionaryKWEntryNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> value
                        );
            std::shared_ptr<Token> GetOperator();
            std::shared_ptr<ExpressionNode> GetValue();

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mValue;
    };
}

