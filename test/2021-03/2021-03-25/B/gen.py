#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

n = 7
m = 8;

# 这是一个图论题的数据生成器，该题目在洛谷的题号为P1339
test_data = IO(file_prefix="input.txt") # 生成 heat[1|2|3].in/out 三组测试数据

test_data.input_writeln(n, m, s, t) # 写入到输入文件里，自动以空格分割并换行

    graph = Graph.graph(n, m, weight_limit=5) # 生成一个n点，m边的随机图，边权限制为5
    test_data.input_writeln(graph) # 自动写入到输入文件里，默认以一行一组u v w的形式输出
