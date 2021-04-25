
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class UnaryMinusNode : protected ExpressionNode
    {
        public:
            UnaryMinusNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> right
                        );

        protected:
            std::shared_ptr<NumberToken> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
    };
}

