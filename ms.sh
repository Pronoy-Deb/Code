#!/bin/bash
# Command to run: bash ms.sh number_of_tests

red='\033[1;91m'
green='\033[1;32m'
blue='\033[1;94m'
magenta='\033[1;95m'
cyan='\033[1;96m'
nc='\033[0m' # No Color

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o op
g++ -O2 -std=c++23 Checker.cpp -o ckr
# g++ -O2 -std=c++23 BruteForce.cpp -o bf

max_time=0

for i in $(seq 1 "$1") ; do
    ./gen > inp

    # timeout 5s ./bf < inp > out1
    # exit_status=$?
    # if [ $exit_status -eq 124 ]; then
    #     echo -e "${magenta}Skipped test $i / $1${nc}"
    #     continue
    # fi

    start_time=$(date +%s%3N)
    ./op < inp > out2
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

    if [ "$elapsed" -gt "$max_time" ]; then
        max_time=$elapsed
    fi

    ./ckr < inp > /dev/null

    if [ $? -ne 0 ] ; then
        echo -e "${red}Wrong answer on test $i${nc}\n${magenta}Sample Input:${nc}"
        cat inp
        # echo -e "${green}Expected Output:${nc}"
        # cat out1
        echo -e "${red}Received Output:${nc}"
        cat out2
        echo -e "\n${blue}Time taken: ${max_time} ms${nc}"
        exit 1
    else echo -e "${green}Passed test $i / $1${nc}"
    fi
done
echo -e "\n${green}Pretests passed!${nc}\n${blue}Time taken: ${max_time} ms${nc}"