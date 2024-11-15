#!/bin/bash
# Command: bash st.sh Number_of_Tests

red='\033[1;91m'
green='\033[1;32m'
blue='\033[1;94m'
magenta='\033[1;95m'
cyan='\033[1;96m'
nc='\033[0m' # No Color

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 BruteForce.cpp -o bf
g++ -O2 -std=c++23 Optimized.cpp -o op

max_time=0

for i in $(seq 1 "$1"); do
    ./gen > inp

    timeout 5s ./bf < inp > out1
    exit_status=$?
    if [ $exit_status -eq 124 ]; then
        echo -e "${magenta}Skipped test $i / $1${nc}"
        continue
    fi

    start_time=$(date +%s%3N)
    timeout 5s ./op < inp > out2
    exit_status=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))
    elapsed=$((elapsed > 5 ? elapsed - 5 : elapsed))

    if [ $exit_status -eq 124 ]; then
        echo -e "${red}Timed Out!${nc}"
        echo -e "${cyan}Sample Input:${nc}"
        cat inp
        echo -e "\n${blue}Time taken: ${elapsed} ms${nc}"
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

    expected=$(tr -d '[:space:]' < out1)
    found=$(tr -d '[:space:]' < out2)

    if [ "$expected" != "$found" ]; then
        mismatch=$(awk ' {
            getline out2_line < "out2";
            split($0, ar1); split(out2_line, ar2);
            for (k = 1; k <= length(ar1) && k <= length(ar2); ++k) {
                if (ar1[k] != ar2[k]) {
                    print NR, k; exit;
                }
            }
            if (length(ar1) != length(ar2)) {
                print NR, (length(ar1) < length(ar2)) ? length(ar1) + 1 : length(ar2) + 1; exit;
            }
        }' out1)

        echo -e "${red}Wrong answer! [$mismatch]${nc}\n${magenta}Sample Input:${nc}"
        cat inp
        echo -e "${green}Expected Output:${nc}"
        cat out1
        echo -e "${red}Received Output:${nc}"
        cat out2
        echo -e "\n${cyan}Time taken: ${max_time} ms${nc}"
        exit 1
    else echo -e "${green}Passed test $i / $1${nc}"
    fi
done

echo -e "\n${green}Pretests passed!${nc}\n${cyan}Time taken: ${max_time} ms${nc}"