#pragma once

#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class AssignStatementNode : public StatementNode
    {
        public:
            AssignStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Node> left,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> ops,
                            std::shared_ptr<std::vector<std::shared_ptr<Node>>> rightNodes,
                            std::shared_ptr<Token> op2
                        );

            std::shared_ptr<Node> GetLeft();
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> GetOperators();
            std::shared_ptr<std::vector<std::shared_ptr<Node>>> GetRightNodes();
            std::shared_ptr<Token> GetOperator2();

        protected:
            std::shared_ptr<Node> mLeft;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mOps;
            std::shared_ptr<std::vector<std::shared_ptr<Node>>> mRightNodes;
            std::shared_ptr<Token> mOp2;
            
    };
}
