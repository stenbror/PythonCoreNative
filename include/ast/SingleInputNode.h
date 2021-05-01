
#include <ast/StatementNode.h>
#include <Token.h>

#include <memory>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class SingleInputNode : protected StatementNode
    {
        public:
            SingleInputNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> newline,
                            std::shared_ptr<StatementNode> right
                        );

        protected:
            std::shared_ptr<Token> mNewline;
            std::shared_ptr<StatementNode> mRight;
    };
}
