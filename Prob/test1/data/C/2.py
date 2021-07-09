#!/usr/bin/env python
from cyaron import * 
for i in range(21, 22):

    test_data = IO(file_prefix="C", data_id=i)

    test_data.input_writeln(100)
    
    for j in range(1, 101):

        n = randint(1, 299)
        m = randint(n + 1, 300)

        test_data.input_writeln(n, m)
        str = String.random(n, charset = "01")
        test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/C/C")

