String :
    Sorting a list of string according to their length in ascending order:
        ls.sort(key=len) or ls1=sorted(ls, key=len)
    
    Sorting a list of string according to their length in descending order:
        ls.sort(reverse=True, key=len) or ls1=sorted(ls, reverse=True, key=len)
    
    Reversing a string :
        r = s[::-1]  or,  r = s.reverse()  or,  r = reversed(s)
    
    Counting the frequency of a character in a string :
        s.count('character')
    
    Counting the frequency of a character in a certain range of a string :
        s.count('character', starting_index, ending_index + 1)
    
    Swapping two characters of a string :
        s = list(s)
        s[0], s[1] = s[1], s[0]
        s = "".join(s)
    
    Sorting a string :
        s = "".join(sorted(s)) or, s = "".join(sorted(s, reverse=True))
    
    Working with substring :
        s[start : end-1 : step]
    
    Turning a string into integer :
        int(s)
    
    Converting a string into uppercase :
        s.upper()
    
    Converting a string into lowercase :
        s.lower()
    
    Making a string of a character of length n :
        s = 'Character' * n
    
    To print all the words of a string :
    for i in s.split():
        print(i)

    Index of first occurence of a substring in a string :
        index = string.find(substring)

    Indices of all occurrences of a substring in a string :
        import re
        occurrences = [m.start() for m in re.finditer(substring, string)]
