#!/bin/bash
clang++ -o ./PythonCoreNative.so -fPIC -shared  -I ../include ../src/Parser/AST/*.cc -std=c++17