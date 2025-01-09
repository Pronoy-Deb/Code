//leftFactoring
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string grammar, part1, part2, commonPrefix, newProduction;
    int i = 0, k = 0, pos = 0;

    cout << "Enter Production (A->): ";
    getline(cin, grammar);

    while (grammar[i] != '|' && grammar[i] != '\0')
    {
        part1 += grammar[i++];
    }

    i++; // Skip the '|'

    while (grammar[i] != '\0')
    {
        part2 += grammar[i++];
    }

    // Find the longest common prefix
    while (k < part1.length() && k < part2.length() && part1[k] == part2[k])
    {
        commonPrefix += part1[k++];
    }


    pos = k; // Position after the common prefix
    newProduction = commonPrefix + "X";

    cout << "\nGrammar Without Left Factoring:\n";
    cout << "A -> " << newProduction << endl;

    if (pos >= part1.length())
    {
        cout << "X -> " << part2.substr(pos) << endl; // Only part2 remains
    }
    else if (pos >= part2.length())
    {
        cout << "X -> " << part1.substr(pos) << endl; // Only part1 remains
    }
    else
    {
        cout << "X -> " << part1.substr(pos) << "|" << part2.substr(pos) << endl;
    }

    return 0;
}

