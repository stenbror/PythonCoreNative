#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class CaseStatementNode : public StatementNode
    {
        public:
            CaseStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1,
                            std::shared_ptr<StatementNode> left,
                            std::shared_ptr<StatementNode> right,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<StatementNode> next
                        );
            std::shared_ptr<NameToken> GetOperator1();
            std::shared_ptr<StatementNode> GetLeft();
            std::shared_ptr<StatementNode> GetRight();
            std::shared_ptr<Token> GetOperator2();
            std::shared_ptr<StatementNode> GetNext();

        protected:
            std::shared_ptr<NameToken> mOp1;
            std::shared_ptr<StatementNode> mLeft;
            std::shared_ptr<StatementNode> mRight;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<StatementNode> mNext;
            
    };
}
