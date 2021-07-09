#!/usr/bin/env python
from cyaron import * 
for i in range(1, 11):

    test_data = IO(file_prefix="pythagorean", data_id=i)

    T = 1
    test_data.input_writeln(T)
    for i in range(1, T + 1): 
        l = randint(1, 200)
        r = randint(300, 500)
        test_data.input_writeln(l, r)

    test_data.output_gen("~/code/Prob/test2/data/pythagorean/pythagorean")

for i in range(11, 21):    
   
    test_data = IO(file_prefix="pythagorean", data_id=i)

    T = 1
    test_data.input_writeln(T)
    for i in range(1, T + 1): 
        l = randint(1, 1000)
        r = randint(1100, 2000)
        test_data.input_writeln(l, r)

    test_data.output_gen("~/code/Prob/test2/data/pythagorean/pythagorean")
