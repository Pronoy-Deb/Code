#!/bin/bash
# Command: bash cpp.sh file.cpp

fileName="$1"

g++ -O2 -std=c++23 -DLOCAL -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter "$fileName" -o l
if [ $? -ne 0 ]; then
    echo -e "\nCompilation error!"
    exit 1
fi

mapfile -t inputs < Sample_Input
mapfile -t expected_outputs < Expected_Output

all_passed=true
failed_tests=()
i=0
exp_i=0
test_num=1
max_time=0

get_test_case_data() {
    local -n data=$1
    local index=$2
    local result=""

    while [ "$index" -lt "${#data[@]}" ] && [[ -n "${data[$index]}" ]]; do
        result+="${data[$index]}\n"
        index=$((index + 1))
    done

    index=$((index + 1))

    echo -e "$result"
    echo "$index"
}

while [ $i -lt "${#inputs[@]}" ] && [ $exp_i -lt "${#expected_outputs[@]}" ]; do
    input_data=$(get_test_case_data inputs $i)
    i=$(echo "$input_data" | tail -n 1)
    input_data=$(echo "$input_data" | head -n -1)

    expected_data=$(get_test_case_data expected_outputs $exp_i)
    exp_i=$(echo "$expected_data" | tail -n 1)
    expected_data=$(echo "$expected_data" | head -n -1)

    if [ -z "$input_data" ] && [ -z "$expected_data" ]; then
        break
    fi

    start_time=$(date +%s%3N)
    echo -e "$input_data" | timeout 5s ./l > out2
    exit_status=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

    if [ $elapsed -gt $max_time ]; then
        max_time=$elapsed
    fi

    actual_output=$(<out2)
    echo "Received Output $test_num:"

    if [ $exit_status -eq 124 ]; then
        echo -e "Timed out!\n"
        all_passed=false
        failed_tests+=("$test_num")
        continue
    elif [ $exit_status -ne 0 ]; then
        echo -e "Runtime error!\n"
        all_passed=false
        failed_tests+=("$test_num")
        continue
    fi

    echo -e "$actual_output\n"

    mismatch=$(awk -v test_num="$test_num" '
        NR == FNR { expected_lines[NR] = $0; expected_line_count = NR; next }
        {
            received_line = $0
            expected_line = expected_lines[FNR]

            if (expected_line == "") {
                print "[" FNR, 1 "]\nExpected: null\nReceived: " received_line
                exit
            }

            split(received_line, ar1)
            split(expected_line, ar2)

            for (i = 1; i <= length(ar1) || i <= length(ar2); ++i) {
                if (ar1[i] != ar2[i]) {
                    print "[" FNR, i "]"
                    print "Expected: " (i <= length(ar2) ? ar2[i] : "null")
                    print "Received: " (i <= length(ar1) ? ar1[i] : "null")
                    exit
                }
            }
        }
        END {
            if (FNR < expected_line_count) {
                print "[" FNR + 1, 1 "]\nExpected: " expected_lines[FNR + 1] "\nReceived: null"
                exit
            }
        }
    ' <(echo -e "$expected_data") out2)

    if [ -n "$mismatch" ]; then
        echo -e "Wrong answer! $mismatch\n"
        all_passed=false
        failed_tests+=("$test_num")
    fi

    test_num=$((test_num + 1))
done

if [ "$all_passed" = true ]; then
    echo "Pretests passed! ($((test_num - 1)))"
else
    echo "Failed tests: ${failed_tests[*]}"
fi

max_time=$((max_time > 5 ? max_time - 5 : max_time))
echo -e "Time taken: ${max_time} ms"
