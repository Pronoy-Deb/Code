#!/bin/bash
# Command: bash cpp.sh file.cpp

fileName="$1"

g++ -O2 -std=c++23 -DLOCAL -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-misleading-indentation "$fileName" -o l

start_time=$(date +%s%N)
timeout 7s ./l < Input > out1
exit_status=$?
end_time=$(date +%s%N)
elapsed=$(((end_time - start_time) / 1000000 ))

if [ $exit_status -eq 124 ]; then
    echo -e "\nTime limit exceeded!\nTime taken: ${elapsed} ms"
    exit 1
fi

echo "Received Output:"
cat out1

expected=$(tr -d '[:space:]' < out1)
found=$(tr -d '[:space:]' < Expected_Output)

if [ "$expected" != "$found" ]; then
    mismatch=$(awk '{
        getline expected_line < "Expected_Output";
        split($0, ar1); split(expected_line, ar2);
            for (k = 1; k <= length(ar1) && k <= length(ar2); ++k) {
                if (ar1[k] != ar2[k]) {
                    print NR, k; exit;
                }
            }
            if (length(ar1) != length(ar2)) {
                print NR, (length(ar1) < length(ar2)) ? length(ar1) + 1 : length(ar2) + 1; exit;
            }
        }' out1)

    echo -e "\nWrong answer! [$mismatch]"
else echo -e "\nPretest passed!"
fi

echo "Time taken: ${elapsed} ms"