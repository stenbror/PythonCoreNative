#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class ClassPatternNode : public StatementNode
    {
        public:
            ClassPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> dots,
                            std::shared_ptr<Token> openCurly,
                            std::shared_ptr<AST::StatementNode> positionals,
                            std::shared_ptr<Token> firstComma,
                            std::shared_ptr<AST::StatementNode> keywords,
                            std::shared_ptr<Token> secondComma,
                            std::shared_ptr<Token> closeCurly
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<NameToken>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mDots;
            std::shared_ptr<Token> mOpenCurly;
            std::shared_ptr<AST::StatementNode> mPositionals;
            std::shared_ptr<Token> mFirstComma;
            std::shared_ptr<AST::StatementNode> mKeywords;
            std::shared_ptr<Token> mSecondComma;
            std::shared_ptr<Token> mCloseCurly;
            
    };
}
