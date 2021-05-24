#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class MappingPatternNode : public StatementNode
    {
        public:
            MappingPatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> openCurly,
                            std::shared_ptr<AST::StatementNode> items,
                            std::shared_ptr<Token> firstComma,
                            std::shared_ptr<AST::StatementNode> doubleStar,
                            std::shared_ptr<Token> secondComma,
                            std::shared_ptr<Token> closeCurly
                        );

            std::shared_ptr<Token> GetOpenCurly();
            std::shared_ptr<AST::StatementNode> GetItems();
            std::shared_ptr<Token> GetFirstComma();
            std::shared_ptr<AST::StatementNode> GetDoubleStar();
            std::shared_ptr<Token> GetSecondComma();
            std::shared_ptr<Token> GetCloseCurly();

        protected:
            std::shared_ptr<Token> mOpenCurly;
            std::shared_ptr<AST::StatementNode> mItems;
            std::shared_ptr<Token> mFirstComma;
            std::shared_ptr<AST::StatementNode> mDoubleStar;
            std::shared_ptr<Token> mSecondComma;
            std::shared_ptr<Token> mCloseCurly;
            
    };
}
