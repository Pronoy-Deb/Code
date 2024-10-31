#!/bin/bash
# Command: bash st.sh Number_of_Tests

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 BruteForce.cpp -o bf
g++ -O2 -std=c++23 Optimized.cpp -o op

max_time=0

for i in $(seq 1 "$1"); do
    ./gen > inp
    
    timeout 5s ./bf < inp > out1
    exit_status=$?
    if [ $exit_status -eq 124 ]; then
        echo "Skipped test $i / $1"
        continue
    fi

    start_time=$(date +%s%3N)
    ./op < inp > out2
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

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

        echo -e "\nWrong answer! [$mismatch]\nInput:"
        cat inp
        echo "Expected Output:"
        cat out1
        echo "Received Output:"
        cat out2
        echo -e "\nTime taken: ${max_time} ms"
        exit 1
    else echo "Passed test $i / $1"
    fi
done

echo -e "\nPretests passed!\nTime taken: ${max_time} ms"