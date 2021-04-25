#!/bin/bash
clang++ -o ./libPythonCoreNative.so.0 -fPIC -shared  -I ../include ../src/Parser/AST/*.cc -std=c++17
ln -s libPythonCoreNative.so.0 libPythonCoreNative.so