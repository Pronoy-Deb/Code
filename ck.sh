#!/bin/bash
#Command: bash ck.sh Number_of_Tests

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o op

for i in $(seq 1 "$1") ; do
    ./gen > inp
    ./op < inp > out2

    echo "Input for test $i:"
    cat inp
    echo "Received Output:"
    cat out2
done