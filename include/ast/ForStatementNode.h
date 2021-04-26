
#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ForStatementNode : protected StatementNode
    {
        public:
            ForStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<Token> op3,
                            std::shared_ptr<Token> op4,
                            std::shared_ptr<StatementNode> next,
                            std::shared_ptr<StatementNode> extra
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<Token> mOp4;
            std::shared_ptr<StatementNode> mNext;
            std::shared_ptr<StatementNode> mExtra;
    };
}
