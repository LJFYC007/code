#!/usr/bin/env python
from cyaron import * 
test_data = IO(file_prefix="A", data_id=16)

n = randint(1, 5000000)
m = randint(1, n // 2)

str = String.random(m)
s = str + str[::-1];
str = String.random(n - m * 2)
s = s + str;
test_data.input_writeln(s)

test_data.output_gen("~/code/Prob/test1/data/A/A")

