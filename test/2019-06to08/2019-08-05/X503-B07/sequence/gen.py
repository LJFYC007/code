#!/usr/bin/env python
import os
main = "~/code/test/2019-08-05/X503-B07/sequence/check"

from cyaron import *

for i in range(1, 1000002):
    test_data = IO(file_prefix="sequence", data_id=1)
    test_data.input_writeln(12)
    s1 = randint(1, 10)
    if s1 % 2 == 1 : continue 
    s2 = s1
    #  s2 = randint(1, 10)
    #  if s2 % 2 == 1 : continue 
    for j in range(1, 13):
        if s1 > 0 : x = randint(0, 1)
        else: x = randint(0, 0)
        if s2 > 0 : y = randint(0, 1)
        else: y = randint(0, 0)
        s1 -= x; s2 -= y;
        test_data.input_writeln(x, y)
    if s1 > 0 : continue 
    if s2 > 0 : continue 
    test_data.output_gen("~/code/test/2019-08-05/X503-B07/sequence/std")
    os.system(main)
