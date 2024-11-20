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

if [ $? -ne 0 ]; then
    echo -e "\n${red}Compilation error!${nc}"
    exit 1
fi

max_time=0

for i in $(seq 1 "$1") ; do
    ./gen > inp

    start_time=$(date +%s%3N)
    timeout 5s ./op < inp > out2
    exit_status=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

    if [ "$elapsed" -gt "$max_time" ]; then
        max_time=$elapsed
    fi

    if [ $exit_status -eq 124 ]; then
        echo -e "${red}Timed out!${nc}"
        echo -e "${cyan}Sample Input:${nc}"
        cat inp
        break
    elif [ $exit_status -ne 0 ]; then
        echo -e "\n${red}Runtime error!${nc}"
        echo -e "${cyan}Sample Input:${nc}"
        cat inp
        break
    fi

    echo -e "${magenta}Input for test $i:${nc}"
    cat inp
    echo -e "${cyan}Received Output $i:${nc}"
    cat out2
done

max_time=$((max_time > 5 ? max_time - 5 : max_time))
echo -e "\n${blue}Time taken: ${max_time} ms${nc}"