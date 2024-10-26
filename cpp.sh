#!/bin/bash
# Command: bash cpp.sh file.cpp

fileName="$1"

g++ -O2 -std=c++23 -DLOCAL -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-misleading-indentation "$fileName" -o l

if [ $? -ne 0 ]; then
    echo -e "\nCompilation error!"
    exit 1
fi

start_time=$(date +%s%3N)
timeout 5s ./l < Input > out2
exit_status=$?
end_time=$(date +%s%3N)
elapsed=$((end_time - start_time))
elapsed=$((elapsed > 5 ? elapsed - 5 : elapsed))

if [ $exit_status -eq 124 ]; then
    echo -e "\nTimed out!\nTime taken: ${elapsed} ms"
    exit 1
elif [ $exit_status -ne 0 ]; then
    echo -e "\nCore dump error!"
    exit 1
fi

echo "Received Output:"
cat out2

expected=$(tr -d '[:space:]' < Expected_Output)
found=$(tr -d '[:space:]' < out2)

if [ "$expected" != "$found" ]; then
    mismatch=$(awk '
        NR == FNR { expected_lines[NR] = $0; next }
        {
            received_line = $0
            expected_line = expected_lines[FNR]

            split(received_line, ar1)
            split(expected_line, ar2)

            for (i = 1; i <= length(ar1) || i <= length(ar2); ++i) {
                if (ar1[i] != ar2[i]) {
                    print "[" FNR, i "]"
                    print "Expected: " (i <= length(ar2) && ar2[i] != "" ? ar2[i] : "null")
                    print "Received: " (i <= length(ar1) && ar1[i] != "" ? ar1[i] : "null")
                    exit
                }
            }

            if (length(ar1) != length(ar2)) {
                print "[" FNR, (length(ar1) < length(ar2) ? length(ar1) + 1 : length(ar2) + 1) "]"
                print "Expected: " (length(ar2) > length(ar1) ? ar2[length(ar2)] : "null")
                print "Received: " (length(ar1) > length(ar2) ? ar1[length(ar1)] : "null")
                exit
            }
        }
    ' Expected_Output out2)

    echo -e "\nWrong answer! $mismatch"
else
    echo -e "\nPretest passed!"
fi

echo "Time taken: ${elapsed} ms"