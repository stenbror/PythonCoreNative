
#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>


namespace PythonCoreNative::RunTime::Parser::AST
{
    class SuiteStatementNode : protected StatementNode
    {
        public:
            SuiteStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<Token> op1,
                            std::shared_ptr<Token> op2,
                            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> nodes,
                            std::shared_ptr<Token> op3
                        );

        protected:
            std::shared_ptr<Token> mOp1;
            std::shared_ptr<Token> mOp2;
            std::shared_ptr<Token> mOp3;
            std::shared_ptr<std::vector<std::shared_ptr<StatementNode>>> mNodes;
    };
}
