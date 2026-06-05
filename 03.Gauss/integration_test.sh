#!/bin/bash

status=true

python3 -c '
import random

random.seed(42)
n = 5

A = []
for i in range(n):
    row = []
    for j in range(n):
        val = random.random()
        if i == j:
            val += n
        row.append(val)
    A.append(row)

x_true = [random.random() for _ in range(n)]

B = []
for i in range(n):
    s = 0.0
    for j in range(n):
        s += A[i][j] * x_true[j]
    B.append(s)

with open("test_in.csv", "w") as f:
    f.write(",".join(["A"]*n + ["B"]) + "\n")
    for i in range(n):
        row_vals = A[i] + [B[i]]
        f.write(",".join(f"{v:.12f}" for v in row_vals) + "\n")

with open("test_expected.csv", "w") as f:
    f.write("A,B\n")
    for x in x_true:
        f.write(f"{x:.6f}\n")
'

./gauss test_in.csv > test_actual.csv

if cmp -s test_expected.csv test_actual.csv; then
    echo "Integration test PASSED!"
else
    echo "Integration test FAILED! Outputs differ:"
    diff test_expected.csv test_actual.csv
    status=false
fi

rm -f test_in.csv test_expected.csv test_actual.csv

if [ "$status" = false ]; then
    exit 1
fi