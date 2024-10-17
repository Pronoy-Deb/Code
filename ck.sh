#!/bin/bash
#Command: bash ck.sh Number_of_Tests

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o op

max_time=0

for i in $(seq 1 "$1") ; do
    ./gen > inp

    start_time=$(date +%s%N)
    ./op < inp > out2
    end_time=$(date +%s%N)

    elapsed=$(( (end_time - start_time) / 1000000 ))
    if [ "$elapsed" -gt "$max_time" ]; then
        max_time=$elapsed
    fi

    echo "Input for test $i:"
    cat inp
    echo "Output:"
    cat out2
done

echo -e "\nTime taken: ${max_time} ms"