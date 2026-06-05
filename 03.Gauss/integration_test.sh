#!/bin/bash

status=true

python3 -c "
import numpy as np
np.random.seed(42)
n = 5
A = np.random.rand(n, n) + np.eye(n) * n
x_true = np.random.rand(n)
B = A @ x_true
AB = np.column_stack((A, B))

with open('test_in.csv', 'w') as f:
    f.write(','.join(['A']*n + ['B']) + '\n')
    np.savetxt(f, AB, delimiter=',', fmt='%.12f')

with open('test_expected.csv', 'w') as f:
    f.write('A,B\n')
    np.savetxt(f, np.column_stack([x_true]), delimiter=',', fmt='%.6f')
"

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