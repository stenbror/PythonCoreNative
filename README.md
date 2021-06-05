# PythonCoreNative

This is the start of a complete Python interpreter, written from scratch in modern C++ 17 and as a first step will implement a complete Roslyn like parser for Python 3.10 grammar.  

Open project in Visual Studio Code and open terminal.

To build:

mkdir -p build  
cd build  
cmake ..  
make  

To execute UnitTests. They are written as we go, execute the following:  

tests/TestPythonCore  

This will result in a dynamic library like on Linux => libPythonCoreNative.so and a UnitTest Executable linked against it. TestPythonCore. 

I develop this project on an Apple MacPro M1 13" and of cource make sure it builds on that system first. But i also check out code and build on Raspberry Pi 4 CM4 machine and a HP Spectre X360 with Ubuntu 21.04 to make sure it builds from checkout of code under Linux. For now i haven't tested building on a Windows machine.  

UnitTests for all EvalInput rules is implemented and passed by June 5th 2021.  
