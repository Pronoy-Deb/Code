Note:
    1. The number substring of a string = (n*(n+1))/2;  // n = |s|
    2. string::npos = 18446744073709551615 = -1((long long)string::npos)

Syntax:
    REVERSING:
        reverse(s.begin(), s.end());

    SORTING:
        sort(s.begin(), s.end());  // ascending order
        sort(s.rbegin(), s.rend());  // descending order
    
    SUBSTRING:
        str.substr(starting_index, length);
        str.substr(starting_index); // prints all the characters from starting index
    
    Converting a String into Number:
        int n = stoi(s);  // for int -> "12345" OR, "12345string"
        long long n = stoll(s);  // for long long
        int n = stoi("1010", nullptr, 2);  // for binary
        int n = stoi("0x6C1", nullptr, 16);  // for hexadecimal

    Coverting a number into string:
        string s = to_string(n);  // any type of number

    To take INPUT a space separated sentence in test cases:
        cin.ignore(); getline(cin, s);
    
    ERASING characters FROM an index TO the end of the string:
        s.erase(index);
    
    ERASING a character:
        s.erase(s.begin() + index);
    
    To CREATE a string of size n consisting of a unique character:
        string s(n, 'character');
    
    CONCATENATION of two strings:
        string s = "Hello", s1 = "World";
        s += s1;  // O(s1.size()), Use instead of s = s+s1;
    
    Adding a CHARACTER to the end of a string:
        s += 'char';  OR,  s.push_back('char');

    To toggle the CASE of a character:
        char('c' ^ ' ')       OR,  char('C' ^ ' ')
    OR, char('c' ^ (1 << 5))  OR,  char('C' ^ (1 << 5))

    To convert a character into UPPERCASE:
        char('c' & '_');  OR,  char('c' & (~(1 << 5)))

    To convert a character into LOWERCASE:
        char('C' | ' ');  OR,  char('C' | (1 << 5))
        
    To convert a string into UPPERCASE:
        transform(s.begin(), s.end(), s.begin(), ::toupper);

    To convert a string into LOWERCASE:
        transform(s.begin(), s.end(), s.begin(), ::tolower);

    To set the number of character & fill value to be printed in a string:
        cout << setw(8) << "hello"; // "  hello"
        cout << setfill('0') << setw(3) << 7; // "007"

    Finding the first and last index of a character:
        s.find('c');  // returns -1((long long)string::npos) if 'c' is absent
        OR, find(s.begin(), s.end(), 'c') - s.begin();
        OR, s.find_first_of('c'); // first index
        OR, s.find_last_of('c') // last index