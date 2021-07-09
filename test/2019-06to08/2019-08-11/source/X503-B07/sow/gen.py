#!/usr/bin/env python

from cyaron import *

import commands
import os

main = "./1"
main2 = "./sow"

for i in range(1, 10001):
    input_io = IO(file_prefix="sow", data_id=1)
    n = 100
    input_io.input_writeln(n)
    for j in range(1, n + 1):
        input_io.input_write(randint(1, 100))
    m = 100
    input_io.input_writeln(m)
    for j in range(1, m + 1):
        input_io.input_writeln(randint(1, n), randint(1, 100))

    os.system(main)
    os.system(main2)
    Compare.output("sow1.out", std = "sow.out") 
