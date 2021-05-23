#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class CapturePatternNode : public StatementNode
    {
        public:
            CapturePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1
                        );
            std::shared_ptr<Token> GetOperator();

        protected:
            std::shared_ptr<Token> mOp1;
            
    };
}
