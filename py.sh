#!/bin/bash
# Command: bash cpp.sh file.cpp

fileName="$1"

red='\033[1;91m'
green='\033[1;32m'
blue='\033[1;94m'
magenta='\033[1;95m'
cyan='\033[1;96m'
nc='\033[0m' # No Color

if [ $? -ne 0 ]; then
    echo -e "\n${red}Compilation error!${nc}"
    exit 1
fi

mapfile -t inputs < Sample_Input
mapfile -t expected_outputs < Expected_Output

if [ ${#expected_outputs[@]} -eq 0 ]; then
    echo -e "${red}\nEmpty Expected Output!${nc}"
    exit 1
fi

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
    echo -e "$input_data" | timeout 5s python3 "$fileName" < Sample_Input > out2
    exit_status=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

    if [ $elapsed -gt $max_time ]; then
        max_time=$elapsed
    fi

    if [ $exit_status -eq 124 ]; then
        echo -e "${red}Timed out!${nc}\n"
        all_passed=false
        failed_tests+=("$test_num")
        continue
    elif [ $exit_status -ne 0 ]; then
        echo -e "${red}Runtime error!${nc}\n"
        all_passed=false
        failed_tests+=("$test_num")
        continue
    fi

    actual_output=$(<out2)

    echo -e "${cyan}Received Output $test_num:${nc}"
    cat out2
    echo ""
    IFS=$'\n' read -d '' -r -a actual_lines <<< "$actual_output"
    IFS=$'\n' read -d '' -r -a expected_lines <<< "$expected_data"

    if [ "${#actual_lines[@]}" -ne "${#expected_lines[@]}" ]; then
        max_lines=$(( ${#actual_lines[@]} > ${#expected_lines[@]} ? ${#actual_lines[@]} : ${#expected_lines[@]} ))
        for (( j=0; j<$max_lines; j++ )); do
            if [ -z "${expected_lines[j]}" ]; then
                echo -e "${red}Wrong answer! ${nc}${blue}[$((j + 1)) 1]${nc}\n${green}Expected: null${nc}\n${red}Received: ${actual_lines[j]}${nc}\n"
                mismatch=true
                break
            elif [ -z "${actual_lines[j]}" ]; then
                echo -e "${red}Wrong answer! ${nc}${blue}[$((j + 1)) 1]${nc}\n${green}Expected: ${expected_lines[j]}${nc}\n${red}Received: null${nc}\n"
                mismatch=true
                break
            fi
        done
        all_passed=false
        failed_tests+=("$test_num")
        continue
    fi

    mismatch=false
    for (( j=0; j<${#expected_lines[@]}; j++ )); do
        expected_line="${expected_lines[j]}"
        actual_line="${actual_lines[j]}"

        IFS=' ' read -r -a expected_columns <<< "$expected_line"
        IFS=' ' read -r -a actual_columns <<< "$actual_line"

        for (( k=0; k<${#expected_columns[@]} || k<${#actual_columns[@]}; k++ )); do
            if [ "${expected_columns[k]}" != "${actual_columns[k]}" ]; then
                echo -e "${red}Wrong answer! ${nc}${blue}[$((j + 1)) $((k + 1))]${nc}"
                echo -e "${green}Expected: ${expected_columns[k]:-null}${nc}"
                echo -e "${red}Received: ${actual_columns[k]:-null}${nc}\n"
                mismatch=true
                break
            fi
        done
        [ "$mismatch" = true ] && break
    done

    if [ "$mismatch" = true ]; then
        all_passed=false
        failed_tests+=("$test_num")
    fi

    test_num=$((test_num + 1))
done

if [ "$all_passed" = true ]; then
    echo -e "${green}Pretests passed! ($((test_num - 1)))${nc}"
else
    echo -e "${magenta}Failed tests: ${failed_tests[*]}${nc}"
fi

max_time=$((max_time > 5 ? max_time - 5 : max_time))
echo -e "${blue}Time taken: ${max_time} ms${nc}"
