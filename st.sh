#!/bin/bash
# Command: bash st.sh Number_of_Tests

g++ -std=c++23 Generator.cpp -o gen
g++ -std=c++23 Brute_Force.cpp -o brute
g++ -std=c++23 Optimized.cpp -o opti

for i in $(seq 1 "$1"); do
    ./gen > inp
    ./brute < inp > out1
    ./opti < inp > out2
    diff -Z out1 out2 > /dev/null

    if [ $? -ne 0 ]; then
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

        echo -e "Wrong answer on test $i [$mismatch]\nInput:"
        cat inp
        echo "Expected:"
        cat out1
        echo "Found:"
        cat out2
        echo ""
        exit 1
    else echo "Passed test $i / $1"
    fi
done

echo -e "Pretests passed successfully!\n"