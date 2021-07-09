#!/usr/bin/env python
from cyaron import * 
for i in range(21, 31):

    test_data = IO(file_prefix="road", data_id=i)

    n = 15
    m = 300
    k = 75
    test_data.input_writeln(n, m, k)
    for i in range(1, m + 1): 
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        w = randint(1, 10)
        c = randint(3, 10)
        test_data.input_writeln(u, v, w, c)

    test_data.output_gen("~/code/Prob/test2/data/road/road")
