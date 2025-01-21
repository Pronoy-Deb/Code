// SortedSet:
    var st = new SortedSet<int>();

// Array of SortedSet:
    var st = new SortedSet<int>[n];
    for (int i = 0; i < n; ++i) st[i] = new SortedSet<int>();

// Operation:
    st.Add(x); // Add element x to the Set
    st.Remove(x); // Remove element x from the Set
    st.Contains(x); // Check whether the Set contains element x
    st.Clear(); // Remove all elements from the Set

// HashSet: Unsorted set
    var hst = new HashSet<int>();
    OR, var hst = new HashSet<int>(n); // HashSet of size n

// Operation:
    hst.Add(x); // Add element x to the HashSet
    hst.Remove(x); // Remove element x from the HashSet
    int n = hst.Count; // Get the number of elements in the HashSet
    hst.Contains(x); // Check whether the HashSet contains element x
    hst.Clear(); // Remove all elements from the HashSet
    // Traverse all
    foreach (int i in hst) {
        Console.WriteLine(i);
    }
    hst.UnionWith(hst1); // Union of two hash sets
    hst.IntersectWith(hst1); // Intersection of two hash sets
    hst.ExceptWith(hst1); // Difference of two hash sets
    hst.SymmetricExceptWith(hst1); // Symmetric difference of two hash sets
    hst.IsSubsetOf(hst1); // Check whether the current HashSet is a subset of hst1
    hst.IsSupersetOf(hst1); // Check whether the current HashSet is a superset of hst1
    hst.IsProperSupersetOf(hst1); // Check whether the current HashSet is a proper superset of hst1
    hst.IsProperSubsetOf(hst1); // Check whether the current HashSet is a proper subset of hst1
    hst.SetEquals(hst1); // Check whether the current HashSet is equal to hst1
    hst.AddRange(hst1); // Add all elements from hst1 to the current HashSet
    hst.CopyTo(array, 0); // Copy all elements from the current HashSet to the array
    hst.RemoveWhere(x => x % 2 == 0); // Remove all elements divisible by 2 from the current HashSet
    hst.TrimExcess(); // Trim the size of the current HashSet to match the number of unique elements

// Hashtable:
// Inclusion:
    using System.Collections;

// Declaration:
    var ht = new Hashtable();