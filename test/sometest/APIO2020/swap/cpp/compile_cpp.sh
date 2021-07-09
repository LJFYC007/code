#!/bin/bash

problem=swap

g++ -std=c++11 -o "${problem}" "grader.cpp" "${problem}.cpp" -lm && ./swap
