
#include <ast/StatementNode.h>
#include <ast/ExpressionNode.h>
#include <Token.h>

#include <memory>
#include <vector>

namespace PythonCoreNative::RunTime::Parser::AST
{
    class VarArgsListStatementNode : protected StatementNode
    {
        public:
            VarArgsListStatementNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> nodes,
                            std::shared_ptr<std::vector<std::shared_ptr<Token>>> separators,
                            std::shared_ptr<Token> slash,
                            std::shared_ptr<Token> mul,
                            std::shared_ptr<StatementNode> mulNode,
                            std::shared_ptr<Token> power,
                            std::shared_ptr<StatementNode> powerNode
                        );

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<ExpressionNode>>> mNodes;
            std::shared_ptr<std::vector<std::shared_ptr<Token>>> mSeparators;
            std::shared_ptr<Token> mSlash;
            std::shared_ptr<Token> mMul;
            std::shared_ptr<StatementNode> mMulNode;
            std::shared_ptr<Token> mPower;
            std::shared_ptr<StatementNode> mPowerNode;
    };
}
