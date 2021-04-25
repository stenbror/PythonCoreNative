
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomDictionaryNode : protected ExpressionNode
    {
        public:
            AtomDictionaryNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NumberToken> op1,
                            std::shared_ptr<ExpressionNode> right,
                            std::shared_ptr<NumberToken> op2
                        );

        protected:
            std::shared_ptr<NumberToken> mOp1;
            std::shared_ptr<ExpressionNode> mRight;
            std::shared_ptr<NumberToken> mOp2;
    };
}
