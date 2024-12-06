#include <bits/stdc++.h>
using namespace std;

// Number of iterations for testing
const int it = 100;

int32_t main() {
    // Compile the solutions and generator
    string correct_compile = "g++ -std=c++17 -O2 -o correct correct.cpp";
    string wrong_compile = "g++ -std=c++17 -O2 -o wrong wrong.cpp";
    string generator_compile = "g++ -std=c++17 -O2 -o generator generator.cpp";

    system(correct_compile.c_str());
    system(wrong_compile.c_str());
    system(generator_compile.c_str());

    // Timer for execution
    auto start_time = clock();
    for (int t = 1; t <= it; t++) {
        cerr << "Running test case #" << t << "...\n";
        string generate_case = "./generator > input.txt";
        system(generate_case.c_str());
        string run_correct = "./correct < input.txt > correct_solution.txt";
        system(run_correct.c_str());
        string run_wrong = "./wrong < input.txt > wrong_solution.txt";
        system(run_wrong.c_str());
        ifstream correct_file("correct_solution.txt");
        ifstream wrong_file("wrong_solution.txt");
        string ex((istreambuf_iterator<char>(correct_file)), istreambuf_iterator<char>());
        string fo((istreambuf_iterator<char>(wrong_file)), istreambuf_iterator<char>());
        correct_file.close();
        wrong_file.close();
        if (ex != fo) {
            cout << "MISMATCH FOUND in test case #" << t << "!\n";
            cerr << "MISMATCH FOUND in test case #" << t << "!\n";
            cout << "Check 'input.txt', 'correct_solution.txt', and 'wrong_solution.txt' for details.\n";
            cerr << "Time taken = " << 1.0 * (clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";
            return 1; // Exit with error
        }
    }
    cout << "No mismatches found in " << it << " test cases!\n";
    cerr << "Total time taken = " << 1.0 * (clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";
    return 0; // Exit successfully
}




#include <bits/stdc++.h>
using namespace std;

// the following script is for unix systems, for windows please change accordingly

const int it = 100; // select the number of iterations

// populate and save the correct, wrong and generator files
int32_t main()
{
    string correct = "g++-11 -o ./correct ./correct.cpp";
    system(correct.c_str()); // compiling the correct solution
    string wrong = "g++-11 -o ./wrong ./wrong.cpp";
    system(wrong.c_str()); // compiling the wrong solution
    string generator = "g++-11 -o ./generator ./generator.cpp";
    system(generator.c_str()); // compiling the generator

    auto st = clock();
    for (int t = 1; t <= it; t++)
    {
        cerr << "Trying for the " << t << "-th time :((\n";

        string in = "input.txt";
        string generator = "./generator > ./input.txt";
        system(generator.c_str()); // generating a case

        string correct_solution = "./correct < ./input.txt > ./correct_solution.txt";
        system(correct_solution.c_str());

        string wrong_solution = "./wrong < ./input.txt > ./wrong_solution.txt";
        system(wrong_solution.c_str());

        ifstream correct_file;
        correct_file.open("correct_solution.txt"); // opening correct solution file
        string ex = "", line;
        while (getline(correct_file, line, '.'))
        { // reading every line including spaces and newlines
            ex += line;
        }

        ifstream wrong_file;
        wrong_file.open("wrong_solution.txt"); // opening wrong solution file
        string fo = "";
        while (getline(wrong_file, line, '.'))
        { // reading every line including spaces and newlines
            fo += line;
        }

        if (ex != fo)
        {
            cout << "MISMATCH FOUND while running test case " << t << "\n\n";
            cerr << "MISMATCH FOUND while running test case " << t << "\n\n";
            cout << "Check the input.txt file to find the case, correct_solution.txt to find the correct output and similarly check the wrong_solution.txt\n";
            cerr << "Time taken = " << 1.0 * (clock() - st) / CLOCKS_PER_SEC << "s\n";
            exit(0);
        }

        correct_file.close();
        wrong_file.close();
    }
    cout << "No cases found!\n";
    cerr << "No cases found!\n";
    cerr << "Time taken = " << 1.0 * (clock() - st) / CLOCKS_PER_SEC << "s\n";
    return 0;
}