
#include <ast/Node.h>

using namespace PythonCoreNative::RunTime::Parser::AST;

Node::Node(unsigned int start, unsigned int end)
{
    mColStart = start; mColEnd = end;
}