#!/usr/bin/python

import random

random.seed()

f = file("input1.txt", "w")
n = 100

a = [[0] * n for x in xrange(n)]

for i in range(0, n):
	for j in range(i, n):
		k = random.randint(0, 499)
		if (i != j):
			a[i][j] = k
			a[j][i] = k

f.write(str(n) + "\n")
for row in a:
	s = "".join(str(row)).replace(",", "").replace("[", "").replace("]", "")
	f.write(s + "\n")

f.close()