
#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class PassStatementNode : protected StatementNode
    {
        public:
            PassStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        );

        protected:
            std::shared_ptr<Token> mOp1;
    };
}
