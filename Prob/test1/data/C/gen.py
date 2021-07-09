#!/usr/bin/env python
from cyaron import * 
for i in range(1, 5):

    test_data = IO(file_prefix="C", data_id=i)

    test_data.input_writeln(1)

    n = 8
    m = 10

    test_data.input_writeln(n, m)
    str = String.random(n, charset = "01")
    test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/C/C")

for i in range(5, 11):

    test_data = IO(file_prefix="C", data_id=i)

    test_data.input_writeln(10)
    
    for j in range(1, 11):

        n = randint(1, 19)
        m = randint(n + 1, 20)

        test_data.input_writeln(n, m)
        str = String.random(n, charset = "01")
        test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/C/C")

for i in range(11, 13):

    test_data = IO(file_prefix="C", data_id=i)

    test_data.input_writeln(100)
    
    for j in range(1, 101):

        n = randint(1, 50)
        m = n

        test_data.input_writeln(n, m)
        str = String.random(n, charset = "01")
        test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/C/C")

for i in range(13, 21):

    test_data = IO(file_prefix="C", data_id=i)

    test_data.input_writeln(100)
    
    for j in range(1, 101):

        n = randint(1, 199)
        m = randint(n + 1, 200)

        test_data.input_writeln(n, m)
        str = String.random(n, charset = "01")
        test_data.input_writeln(str)

    test_data.output_gen("~/code/Prob/test1/data/C/C")

