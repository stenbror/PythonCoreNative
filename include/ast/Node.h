
namespace PythonCoreNative::RunTime::Parser::AST
{
    class Node
    {
        protected:
            Node(unsigned int start, unsigned int end);

        protected:
            unsigned int mColStart;
            unsigned int mColEnd;
    };

}
