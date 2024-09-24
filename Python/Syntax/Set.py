Note: set allows mixed data types

# O(log(n)) Operations:
from sortedcontainers import SortedSet
st = SortedSet([1, 2, 4, 5])
st.add  (3) # Insertion is O(log n)
print(3 in st) # Search is O(log n)
st.remove(2) # Deletion is O(log n)

Declaring a set:  st = set()

Adding an element:  st.add(ele)

Concatenating set with another container:  st.update(dic)

Removing an element from set:  st.discard(ele)

Checking all elements of the set are True or the set is empty:  all(st)

Checking any element of the set is True, returns False if the set is empty:  any(st)

Returns an enumerate object. It contains the index and value for all the items of the set as a pair:  enumerate()

Length (the number of items) in the set:  len(st)

Largest item in the set:  max(st)

Smallest item in the set:  min(st)

Sorting list from elements in the set(does not sort the set itself):  sorted()

Sum of all elements in the set:  sum(st)

Union of two sets:  st | st1  OR,  st.union(st1)

Intersection of two sets:  st & st1  OR,  st.intersection(st1)

Difference between two sets:  st - st1  OR,  st.difference(st1)

Symmetric difference between two sets:  st ^ st1  OR,  st.symmetric_difference(st1)

Removing all elements from the set:  st.clear()

copy(st): Returns a copy of the set

difference(): Returns the difference of two or more sets as a new set

difference_update(): Removes all elements of another set from this set

intersection_update(): Updates the set with the intersection of itself and another

isdisjoint(): Returns True if two sets have a null intersection

issubset(): Returns True if another set contains this set

issuperset(): Returns True if this set contains another set

pop(): Removes and returns an arbitrary set element. Raises KeyError if the set is empty

remove(): Removes an element from the set. If the element is not a member, raises a KeyError

symmetric_difference(): Returns the symmetric difference of two sets as a new set

symmetric_difference_update(): Updates a set with the symmetric difference of itself and another

update(): Updates the set with the union of itself and others

