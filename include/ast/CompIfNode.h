
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class CompIfNode : protected ExpressionNode
    {
        public:
            CompIfNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<ExpressionNode> next
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<ExpressionNode> mNext;
    };
}
