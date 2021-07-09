@echo off

set problem=jumps
set grader_name=stub

g++ -std=c++11 -O2 -pipe -o "%problem%" "%grader_name%.cpp" "%problem%.cpp"

.\"%problem%.exe