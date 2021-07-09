#!/usr/bin/env python
from cyaron import *

test_data = IO(file_prefix="haha", data_id=1)

for i in range (1, 10776):    
     a, b = map(int, raw_input().split())
     test_data.output_writeln(b % 1000000007)
