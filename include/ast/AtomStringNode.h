
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class AtomStringNode : protected ExpressionNode
    {
        public:
            AtomStringNode(unsigned int start, unsigned int end, std::shared_ptr<std::vector<StringToken>> ops);

        protected:
            std::shared_ptr<std::vector<StringToken>> mOps;
    };
}
