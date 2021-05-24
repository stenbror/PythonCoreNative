# PythonCoreNative

This is the start of a complete Python interpreter, written from scratch in modern C++ 17 and as a first step will implement a complete Roslyn like parser for Python 3.10 grammar.  

Open project in Visual Studio Code and open terminal.

To build:

mkdir -p build  
cd build  
cmake ..  
make  

To execute future UnitTests. Only started on UnitTests for now, execute the following:  

tests/TestPythonCore  

This will result in a dynamic library like on Linux => libPythonCoreNative.so and a UnitTest Executable linked against it. TestPythonCore. 

I develope this project on an Apple MacPro M1 13" and ofcource make sure it builds on this system first. But i also check out code and build on Raspberry Pi 4 CM4 machine and a HP Spectre X360 with Ubuntu 21.04 to make sure it builds from checkout of code. For now i havent tested building on a Windows machine. 
