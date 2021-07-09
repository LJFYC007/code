#!/usr/bin/env python
from cyaron import * 
for i in range(1, 5):

    test_data = IO(file_prefix="A", data_id=i)

    n = randint(1, 12)
    m = randint(1, n // 2)

    str = String.random(m)
    s = str + str[::-1];
    str = String.random(n - m * 2)
    s = s + str;
    test_data.input_writeln(s)

    test_data.output_gen("~/code/Prob/test1/data/A/A")

for i in range(5, 9):

    test_data = IO(file_prefix="A", data_id=i)

    n = randint(1, 1000)
    m = randint(1, n // 2)

    str = String.random(m)
    s = str + str[::-1];
    str = String.random(n - m * 2)
    s = s + str;
    test_data.input_writeln(s)

    test_data.output_gen("~/code/Prob/test1/data/A/A")

for i in range(9, 11):

    test_data = IO(file_prefix="A", data_id=i)

    n = 10000000

    str = String.random(n)
    test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/A/A")

for i in range(11, 21):

    test_data = IO(file_prefix="A", data_id=i)

    n = 10000000
    m = 2000000

    str = String.random(m)
    s = str + str[::-1];
    str = String.random(m, charset="hhhhhhhhhh")
    s = str + s;
    s = s + str + str;
    test_data.input_writeln(s)

    test_data.output_gen("~/code/Prob/test1/data/A/A")
