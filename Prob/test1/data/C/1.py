#!/usr/bin/env python
from cyaron import * 
test_data = IO(file_prefix="C100", data_id=1)

test_data.input_writeln(100)
    
for j in range(1, 101):

    n = randint(1, 49)
    m = randint(n + 1, 50)

    test_data.input_writeln(n, m)
    str = String.random(n, charset = "01")
    test_data.input_writeln(str)

test_data.output_gen("~/code/Prob/test1/data/C/std")

