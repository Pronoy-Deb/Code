# List:
#     Taking values as elements of a 1D list:
        ls = list(map(int, input().split()))
        OR, ls = [int(i) for i in input().split()]

    # Taking values as elements of a 2D list:
        ls = [list(map(int, input().split())) for i in range row]

    # Finding out the length of a list or a string:
        len(ls)  or ,  len(s)

    # Summation of all the elements of a list:
        tot = sum(lis)

    # Summation of all the elements of a 2-D list:
        tot = sum(map(sum, ls))

    # Summation of the elements of a list in a certain range:
        tot = sum(ls[0:len(n)])

    # Sorting a list in ascending order:
        ls.sort() or , ls1 = sorted(ls)

    # Sorting a list in descending order:
        ls.sort(reverse=1) or , ls1 = sorted(ls, reverse=1)

    # Assigning all the elements of a 1D list as 0:
        ls = [0] * Number_of_Elements

    # Assigning all the elements of a 2D list as 0:
        ls = [[0] for _ in range(Number_of_Rows)]

    # Maximum value of a list:
        max(ls)

    # Minimum value of a list:
        min(ls)

    # Index of the maximum value of a list:
        ls.index(max(ls))

    # Index of the minimum value of a list:
        ls.index(min(ls))

    # Counting a number or character in a list or string :
        ls.count(element)  or,  s.count(character)

    # Swapping two elements of a list:
        ls[0], ls[1] = ls[1], ls[0]

    # Counting the frequency of an element in a 2-D list :
    #     fre = 0
    #     for i in lis:
    #         print(lis.count(i[0:]))

    # Taking input of a 2-D list:
        r, c = map(int, input().split())
        ls = []
        for i in range(r):
            ls.append(list(map(int, input().split())))

    # Printing space between list elements:
        print(ls[i], end = ' ')

    # Maximum value of a 2-D list:
        max(max(ls, key=max))

    # Finding out the maximum frequent element of a list:
        max(set(ls), key=ls.count)

    # Finding out the frequency of the maximum frequent element of a list:
        ls.count(max(set(ls), key=ls.count))

    # Counting the number of distinct elements of a list:
        len(set(ls))

    # Accessing elements of a list:
        Last element: ls[-1], Second last element: ls[-2]

    # Checking the presence of element in a 2-D list:
        for i in ls:
            if element in i[0:]:
                print("YES")

    # Concatenating two lists:
        ls.extend(ls1)

    # Deleting elements from the list:
        del ls[index]  OR,  del ls[start_index : number_of_elements]
        ls.remove(ele)  # Removes first occurance of the element

    # List of pairs:
        ls = [(0, 0)] * n
        print(ls[0][0], ls[0][1])

    # insert(): inserts an item at the specified index

    # remove(): removes item present at the given index

    # pop(): returns and removes item present at the given index

    # clear(): removes all items from the list

    # index(): returns the index of the first matched item

    # count(): returns the count of the specified item in the list

    # reverse(): reverses the item of the list

    # copy(): returns the shallow copy of the list
