#!/bin/bash
#Command: bash ck.sh Number_of_Tests

red='\033[1;91m'
green='\033[1;32m'
blue='\033[1;94m'
magenta='\033[1;95m'
cyan='\033[1;96m'
nc='\033[0m' # No Color

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o op

for i in $(seq 1 "$1") ; do
    ./gen > inp

    start_time=$(date +%s%3N)
    timeout 5s ./op < inp > out2
    exit_status=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))
    elapsed=$((elapsed > 5 ? elapsed - 5 : elapsed))

    if [ $exit_status -eq 124 ]; then
        echo -e "${red}Time Limit Exceeded!${nc}"
        echo -e "${cyan}Sample Input:${nc}"
        cat inp
        echo -e "\n${cyan}Time taken: ${elapsed} ms${nc}"
        exit 1
    elif [ $exit_status -ne 0 ]; then
        echo -e "\n${red}Runtime error!${nc}"
        echo -e "${cyan}Sample Input:${nc}"
        cat inp
        exit 1
    fi

    if [ "$elapsed" -gt "$max_time" ]; then
        max_time=$elapsed
    fi

    echo -e "${magenta}Input for test $i:${nc}"
    cat inp
    echo -e "${cyan}Received Output:${nc}"
    cat out2
done

echo -e "\n${cyan}Time taken: ${max_time} ms${nc}"