#!/bin/bash
# Command to run: bash ms.sh number_of_tests

# sed -i 's/\r$//' ms.sh

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o op
g++ -O2 -std=c++23 Checker.cpp -o ckr

max_time=0

for i in $(seq 1 "$1") ; do
    ./gen > inp

    start_time=$(date +%s%N)
    (
        ./op < inp > out2
    )
    end_time=$(date +%s%N)

    elapsed=$(((end_time - start_time) / 1000000 ))
    if [ "$elapsed" -gt "$max_time" ]; then
        max_time=$elapsed
    fi

    ./ckr < inp > /dev/null

    if [ $? -ne 0 ] ; then
        echo -e "Wrong answer on test $i\nInput:"
        cat inp
        echo "Received Output:"
        cat out2
        echo -e "\nTime taken: ${max_time} ms"
        exit 1
    else echo "Passed test $i / $1"
    fi
done
echo -e "Pretests passed!\nTime taken: ${max_time} ms"