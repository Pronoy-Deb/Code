from sortedcontainers import SortedList

# Declaration similar to oset<int>
st = SortedList()

# Inserting elements (like st.insert(a))
for i in range(1, 11):
    a = int(input()); st.add(a)

# Deleting an element (like st.erase(st.find(2)))
if 2 in st: st.remove(2)

# Deleting 2 from the multiset (simulated)
if 2 in st: st.remove(2)  # This removes the first occurrence of 2

# Finding the second element in the set
print(st[1])

# Number of elements strictly less than k = 4
print(st.bisect_left(4))
