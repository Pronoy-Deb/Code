# Dictionary:
    # Declaring a dctionary:
        dc = {}  # empty dctionary
        dc = {key:value, key1:value1}  # valued dctionary

    # Default Dictionary: (With default value as map)
        from collections import defaultdict
        dc = defaultdict(int)


    # Assigning keys and values in a dctionary:
        dc[key] = value  # for one key
        dc[(key, key)] = value  # for more than one key

    # Assigning keys and values in a dctionary with duplicate keys:
    dc = {}
    for i in range(n):
        if ls[i] not in dc: dc[ls[i]] = [i]
        else: dc[ls[i]].append(i)

    # Printing all the keys of a dctionary:
        for e in dc.keys(): print(e)

    # Printing all the values of a dctionary:
        for e in dc.values(): print(i)

    # Printing all the keys and values of a dctionary:
        for k,v in dc.items(): print(k,v)

    # Printing the value of a dctionary using its key:
        print(dc[key])

    # Checking whether a key is present or not:
        if key in dc: