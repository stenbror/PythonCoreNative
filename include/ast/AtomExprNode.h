
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomExprNode : protected ExpressionNode
    {
        public:
            AtomExprNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> left,
                            std::shared_ptr<std::vector<ExpressionNode>> right
                        );

        protected:
            std::shared_ptr<NumberToken> mOp1;
            std::shared_ptr<ExpressionNode> mLeft;
            std::shared_ptr<std::vector<ExpressionNode>> mRight;
    };
}
