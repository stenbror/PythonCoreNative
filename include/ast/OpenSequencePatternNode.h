#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class OpenSequencePatternNode : public StatementNode
    {
        public:
            OpenSequencePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators
                        );

            bool IsGroupPattern();

            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> GetNodes();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetSeparators();

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<AST::StatementNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            
    };
}
