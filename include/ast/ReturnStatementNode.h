
#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ReturnStatementNode : protected StatementNode
    {
        public:
            ReturnStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<StatementNode> mRight;
            
    };
}
