
#include <ast/CapturePatternNode.h>

using namespace PythonCoreNative::RunTime::Parser::AST;
using namespace PythonCoreNative::RunTime::Parser;

CapturePatternNode::CapturePatternNode(  
                            unsigned int start, unsigned int end, 
                            std::shared_ptr<NameToken> op1
                        ) : StatementNode(start, end)
{
    
    mOp1 = op1;

}

std::shared_ptr<Token> CapturePatternNode::GetOperator()
{
    return mOp1;
}
