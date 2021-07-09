#!/usr/bin/env python
from cyaron import * 
test_data = IO(file_prefix="B123", data_id=2)

n = 1000
q = randint(100000, 1000000000000)
x = randint(1, 10)
p = q // x

test_data.input_writeln(n, p, q)
test_data.input_write(q - p * x)
for j in range(2, n + 1):
    y = randint(1, 3)
    if y == 1 : test_data.input_write(x)
    elif y == 2 : test_data.input_write(q - p * x)
    else : test_data.input_write(randint(1, 100000)) 

test_data.output_gen("~/code/Prob/test1/data/B/B")
