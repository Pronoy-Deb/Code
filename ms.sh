#!/bin/bash
# Command to run: bash ms.sh <number_of_tests>
# Example: bash ms.sh 100
sed -i 's/\r$//' ms.sh

g++ -O2 -std=c++23 Generator.cpp -o gen
g++ -O2 -std=c++23 Optimized.cpp -o opti
g++ -O2 -std=c++23 Checker.cpp -o checker

for i in $(seq 1 "$1") ; do
    ./gen > inp
    ./opti < inp > out2
    ./checker < inp > /dev/null

    if [ $? -ne 0 ] ; then
        echo -e "Wrong answer on test $i\nInput:"
        cat inp
        echo "Output:"
        cat out2
        echo ""
        exit 1
    else
        echo "Passed test $i / $1"
    fi
done
echo -e "Pretests passed successfully!\n"