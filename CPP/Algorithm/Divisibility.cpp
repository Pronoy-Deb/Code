// Complexity: O(|s|)

Divisibility by 2: // If the last digit is even

bool d2(auto &s) {
    return (~(s.back() - 48) & 1);
}

Divisibility by 3: // If the summation of the digits is divisible by 3

bool d3(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return !(sum % 3);
}

Divisibility by 4: // If the number consisting of last two digits is divisible by 4

bool d4(auto &s) {
    return !((((s[s.size() - 2] - 48) * 10) + (s.back() - 48)) % 4);
}

Divisibility by 5: // If the last digit is 0 or 5

bool d5(auto &s) {
    return (s.back() == '0' or s.back() == '5');
}

Divisibility by 6: // If the number is divisible by both 2 and 3

bool d6(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return (!(sum % 3) and !((s.back() - 48) & 1));
}

Divisibility by 7: //

Divisibility by 8: // If the number consisting of last three digits is divisible by 8

bool d8(auto &s) {
    int sz = s.size();
    return !((((s[sz - 3] - 48) * 100) + ((s[sz - 2] - 48) * 10) + (s[sz - 1] - 48)) % 8);
}

Divisibility by 9: // If the summation of the digits is divisible by 9

bool d9(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return !(sum % 9);
}

Divisibility by 10: // If the last digit is 0

bool d10(auto &s) {
    return (s.back() == '0');
}

Divisibility by 11: // If the difference of the summation of alternating digits is divisible by 11

bool d11(auto &s) {
    int sum = 0, sz = s.size();
    for (int i = 0; i < sz; ++i) {
        if (i & 1) sum -= (s[i] - 48);
        else sum += (s[i] - 48);
    }
    return !(sum % 11);
}

Divisibility by 12: // If the number is divisible by both 3 and 4

bool d12(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return (!((((s[s.size() - 2] - 48) * 10) + (s.back() - 48)) % 4) and !(sum % 3));
}

Divisibility by 15: // If the number is divisible by both 3 and 5

bool d15(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return ((s.back() == '0' or s.back() == '5') and !(sum % 3));
}

Divisibility by 18: // If the number is divisible by both 2 and 9

bool d18(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return (!(sum % 9) and !((s.back() - 48) & 1));
}

Divisibility by 45: // If the number is divisible by both 5 and 9

bool d45(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return ((s.back() == '0' or s.back() == '5') and !(sum % 9));
}