#!/usr/bin/env python
from cyaron import * 
for i in range(1, 11):

    test_data = IO(file_prefix="road", data_id=i)

    n = 5 
    m = 100
    k = 25
    test_data.input_writeln(n, m, k)
    for i in range(1, m + 1): 
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        w = randint(1, 10)
        c = randint(3, 10)
        test_data.input_writeln(u, v, w, c)

    test_data.output_gen("~/code/Prob/test2/data/road/road")

for i in range(11, 21):

    test_data = IO(file_prefix="road", data_id=i)

    n = 8 
    m = 160
    k = 40
    test_data.input_writeln(n, m, k)
    for i in range(1, m + 1): 
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        w = randint(1, 10)
        c = randint(3, 10)
        test_data.input_writeln(u, v, w, c)

    test_data.output_gen("~/code/Prob/test2/data/road/road")

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

for i in range(31, 41):

    test_data = IO(file_prefix="road", data_id=i)

    n = 17 
    m = 350
    k = 85
    test_data.input_writeln(n, m, k)
    for i in range(1, m + 1): 
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        w = randint(1, 10)
        c = randint(3, 10)
        test_data.input_writeln(u, v, w, c)

    test_data.output_gen("~/code/Prob/test2/data/road/road")

for i in range(41, 51):

    test_data = IO(file_prefix="road", data_id=i)

    n = 20 
    m = 400
    k = 100
    test_data.input_writeln(n, m, k)
    for i in range(1, m + 1): 
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        w = randint(1, 10)
        c = randint(3, 10)
        test_data.input_writeln(u, v, w, c)

    test_data.output_gen("~/code/Prob/test2/data/road/road")
