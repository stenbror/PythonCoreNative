
#pragma once

namespace PythonCoreNative::RunTime::Parser::AST
{
    class Node
    {
        protected:
            Node(unsigned int start, unsigned int end);

        public:
            unsigned int GetNodeStartPosition();
            unsigned int GetNodeEndPosition();

        protected:
            unsigned int mColStart;
            unsigned int mColEnd;
    };

}
