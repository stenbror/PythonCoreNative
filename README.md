# PythonCoreNative

This is the start of a complete Python interpreter, written from scratch in modern C++ 17 and as a first step will implement a complete Roslyn like parser for Python 3.10 grammar.  

Open project in Visual Studio Code and open terminal.

To build:

mkdir -p build  
cd build  
cmake ..  
make  

To execute future UnitTests. Only dummy test for now, execute the following:  

tests/TestPythonCore  

This will result in a dynamic library like on Linux => libPythonCoreNative.so and a UnitTest Executable linked against it. TestPythonCore
