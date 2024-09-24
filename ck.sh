#!/bin/bash
#Command: bash ck.sh 10

g++ -std=c++23 Generator.cpp -o gen
g++ -std=c++23 Optimized.cpp -o opti

for i in $(seq 1 "$1") ; do
    ./gen > inp
    ./opti < inp > out2
    echo "Input for test $i:"
    cat inp
    echo "Output:"
    cat out2
done
echo ""