
#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class ContinueStatementNode : protected StatementNode
    {
        public:
            ContinueStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1
                        );

        protected:
            std::shared_ptr<Token> mOp1;
    };
}
