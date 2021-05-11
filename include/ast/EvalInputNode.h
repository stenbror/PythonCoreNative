#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class EvalInputNode : public StatementNode
    {
        public:
            EvalInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> newlines,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> eof
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mNewlines;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Token> mEof;
    };
}
