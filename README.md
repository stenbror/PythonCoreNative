# PythonCoreNative

This is a test of a modern C++ based Python parser. Just started, but parser is soon implemented, Tokenizer next and UnitTests.
Open project in Visual Studo Code and open terminal.

To build:

mkdir -p build  
cd build  
cmake ..  
make  

To execute future UnitTests. Only dummy test for now, execute the following:  

tests/TestPythonCore  

This will result in a dynamic library like on Linux => libPythonCoreNative.so and a UnitTest Executable linked against it. TestPythonCore
