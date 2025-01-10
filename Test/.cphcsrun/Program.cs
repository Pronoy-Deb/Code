// C# program to illustrate how to
// remove key/value pairs from
// the sortedlist
using System;
using System.Collections;

class GFG {

	// Main Method
	static public void Main()
	{

		// Creating a sortedlist
		// Using SortedList class
		var my_slist = new SortedList();

		// Adding key/value pairs in SortedList
		// Using Add() method
		// my_slist.Add(1.02, "This");
        var ar = Console.ReadLine().Split();
        Console.WriteLine("{0} {1}", ar[0], ar[1]);
        my_slist.Add(Convert.ToDouble(ar[0]), ar[1]);
		my_slist.Add(1.07, "Is");
		my_slist.Add(1.04, "SortedList");
		my_slist.Add(1.01, "Tutorial");

		foreach(DictionaryEntry pair in my_slist)
		{
			Console.WriteLine("{0} and {1}",
					pair.Key, pair.Value);
		}
		Console.WriteLine();

		// Remove value having 1.07 key
		// Using Remove() method
		my_slist.Remove(1.07);

		// After Remove() method
		foreach(DictionaryEntry pair in my_slist)
		{
			Console.WriteLine("{0} and {1}",
					pair.Key, pair.Value);
		}
		Console.WriteLine();

		// Remove element at index 2
		// Using RemoveAt() method
		my_slist.RemoveAt(2);

		// After RemoveAt() method
		foreach(DictionaryEntry pair in my_slist)
		{
			Console.WriteLine("{0} and {1}",
					pair.Key, pair.Value);
		}
		Console.WriteLine();

		// Remove all key/value pairs
		// Using Clear method
		my_slist.Clear();
		Console.WriteLine("The total number of key/value pairs"+
					" present in my_slist:{0}", my_slist.Count);
	}
}
