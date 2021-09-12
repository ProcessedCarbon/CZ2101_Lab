# Theoretical value of S:
1. We studied the average case of insertion sort vs merge sort and we came up with a value of S = 9, 10, 11.
2. References online sources: -> S about 10.
3. We test the value on our machine. However, due to the small size of array, we can only test the complexity but could not measure the acurate run time of the 2 sort.

# Why using these 3 test case:
1. Reversed Array: **worst case performance for insertion sort**, but is the **best for original merge sort**.
2. Randomized Array: Tend to be in the case in practice. we generate use the **same seed for all iterations**.
3. Sorted Array: **Best for insertion sort**, **not as good for original merge sort**.

# How to benchmark:
1. We tried to avoid any redundant copy as well as instruction in our code.
2. We measure the complexity by counting the number of comparison for each sorting algorithm (modified the function prototype and add a counter).
3. Use **std::chrono** for timing the functions. In order to reduce noise from the system, we run the test multiple iterations and averaging over all the result. However, we expect **a bias** in benchmarking as there is no way to measure exactly the execution time of the sort functions. This bias coming from possible redundancy in our code (the comparison counter) and the execution time of the benchmarking timer, but we expect it to be nelegible comparing to the overall run time of the algorithm.


# Result:
1. Value of S versus runtime/complexity:
2. Benchmarking **Hybrid merge sort** vs **original merge sort**.
