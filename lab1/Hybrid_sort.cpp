#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

// benchmarking the codes.
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

using ll = long long;

// merge function
ll merge(std::vector<int>& target, int l, int m, int r) {
   // number of comparison made.
   ll comparison = 0;
   // vector to store the result.
   std::vector<int> dummy(r - l + 1, 0);
   // index of the left and right sub array.
   int i_left = 0, i_right = 0, i = 0;
   // merge loop
   while ((i_left <= m - l) && (i_right <= r - m - 1)) {
      i = i_left + i_right;
      comparison++;
      if (target[i_left + l] < target[i_right + m + 1]) {
         dummy[i] = target[i_left + l];
         i_left++;
      } else {
         dummy[i] = target[i_right + m + 1];
         i_right++;
      }
   }
   i = i_left + i_right;
   // remaining left
   while (i_left <= m - l) {
      dummy[i] = target[i_left + l];
      i_left++, i++;
   }
   // remaining right
   while (i_right <= r - m - 1) {
      dummy[i] = target[i_right + m + 1];
      i_right++, i++;
   }
   // copy the dummy arr to target arr.
   for (int k = l; k <= r; k++) {
      target[k] = dummy[k - l];
   }

   return comparison;
}

// Original merge sort.
ll merge_sort(std::vector<int>& target, int l, int r) {
   ll comparison = 0;
   if (r - l <= 0) {
      return comparison;
   } else {
      int m = l + (r - l) / 2;
      comparison += merge_sort(target, l, m);
      comparison += merge_sort(target, m + 1, r);
      comparison += merge(target, l, m, r);
   }
   return comparison;
}

// insertion_sort.
ll insertion_sort(std::vector<int>& target, int l, int r) {
   ll comparison = 0;
   if (r - l <= 0) return comparison;
   for (int i = l + 1; i <= r; i++) {
      for (int j = i - 1; j >= l; j--) {
         comparison++;
         if (target[j + 1] < target[j]) {
            std::swap(target[j + 1], target[j]);
         } else {
            break;
         }
      }
   }
   return comparison;
}

// Modified (hybrid) merge sort.
ll hybrid_sort(std::vector<int>& target, int l, int r, int threshold) {
   ll comparison = 0;
   if (r - l < threshold) {
      comparison += insertion_sort(target, l, r);
      return comparison;
   } else {
      int m = l + (r - l) / 2;
      comparison += hybrid_sort(target, l, m, threshold);
      comparison += hybrid_sort(target, m + 1, r, threshold);
      comparison += merge(target, l, m, r);
   }
   return comparison;
}

// Utility function to check if array is sorted.
int check_sorted(std::vector<int>& arr) {
   for (int i = 0; i + 1 < arr.size(); i++) {
      if (arr[i] > arr[i + 1]) {
         std::cout << "Check failed!" << std::endl;
         return 0;
      }
   }
   return 1;
}

// Test 1: reverse Array
std::vector<int> test1(size_t size) {
   std::vector<int> reverse_arr(size, 0);
   for (int i = 0; i < size; i++) {
      reverse_arr[i] = size - i;
   }
   return reverse_arr;
}

// Test 2: randomized Array
std::vector<int> test2(size_t size) {
   std::vector<int> rand_arr(size, 0);
   for (int i = 0; i < size; i++) {
      rand_arr[i] = rand() % 1000000007;
   }
   return rand_arr;
}

// Test 3: Uniform Array
std::vector<int> test3(size_t size) {
   std::vector<int> uniform_arr(size, 0);
   int val = rand() % 1000000007;
   for (int i = 0; i < size; i++) {
      uniform_arr[i] = val;
   }
   return uniform_arr;
}

// Test 4: Sorted Array
std::vector<int> test4(size_t size) {
   std::vector<int> sorted_arr(size, 0);
   for (int i = 0; i < size; i++) {
      sorted_arr[i] = i;
   }
   return sorted_arr;
}

// Benchmarking the codes. [5]
void benchmark_hybrid_merge(std::vector<int>& target, size_t size,
                            size_t threshold, size_t iterations) {
   std::cout << "Benchmarking hybrid-MergeSort vs MergeSort: \n";
   printf("Array size: %d, threshold value: %d, iterations: %d\n", size,
          threshold, iterations);
   // Sort functions are passed by reference, we need a copy to retain the
   // original array.
   std::vector<int> target_copy = target;
   // Store the times.
   std::vector<double> time(iterations);
   duration<double, std::micro> dur;
   double hybridsort_time, mergesort_time, noise;
   // for statistics;
   double mean, std_dev, sq_sum;
   std::vector<double> diff(iterations);
   // To measure algorithm complexity.
   ll HybridSort_comparison, MergeSort_comparison;  // avoid overflow.

   // Hybrid sort.
   printf("Testing HybridSort: \n");
   for (size_t i = 0; i < iterations; i++) {
      // get back the original arr for new iteration.
      target = target_copy;
      // timing the code
      auto t1 = high_resolution_clock::now();
      hybrid_sort(target, 0, size - 1, threshold);
      auto t2 = high_resolution_clock::now();
      dur = t2 - t1;
      time[i] = dur.count();
   }
   // Measure comparison.
   target = target_copy;
   HybridSort_comparison = hybrid_sort(target, 0, size - 1, threshold);

   // Statistics calculation.
   mean = std::accumulate(time.begin(), time.end(), 0.0) / iterations;
   // get diff[i] = time[i] - mean, utilizing parallel execution.
   std::transform(time.begin(), time.end(), diff.begin(),
                  [mean](double x) { return x - mean; });
   // get the sum square of diff, careful for overflow.
   sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   std_dev = std::sqrt(sq_sum / iterations);

   // Out put the result.
   hybridsort_time = mean, noise = std_dev;
   printf(
       "%.1f +- %.2f microseconds over %d runs.\n Number of comparison: %d\n",
       hybridsort_time, noise, iterations, HybridSort_comparison);

   // Do again for MergeSort.
   printf("Testing MergeSort: \n");
   for (size_t i = 0; i < iterations; i++) {
      target = target_copy;
      auto t1 = high_resolution_clock::now();
      merge_sort(target, 0, size - 1);
      auto t2 = high_resolution_clock::now();
      dur = t2 - t1;
      time[i] = dur.count();
   }
   // Measure comparison.
   target = target_copy;
   MergeSort_comparison = merge_sort(target, 0, size - 1);

   mean = std::accumulate(time.begin(), time.end(), 0.0) / iterations;
   std::transform(time.begin(), time.end(), diff.begin(),
                  [mean](double x) { return x - mean; });
   sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   std_dev = std::sqrt(sq_sum / iterations);

   mergesort_time = mean, noise = std_dev;
   printf("%.1f +- %.2f microseconds over %d runs\nNumber of comparison: %d\n",
          mergesort_time, noise, iterations, MergeSort_comparison);
}

///// TO BE IMPLEMENTED ///
// find S value for local machine.
void benchmark_insertion_vs_merge(std::vector<int> target, size_t size,
                                  size_t iterations) {
   std::cout << "Benchmarking InsertionSort vs MergeSort: \n";
   printf("Array size: %d, iterations: %d\n", size, iterations);
   // Sort functions are passed by reference, we need a copy to retain the
   // original array.
   std::vector<int> target_copy = target;
   // Store the times.
   std::vector<double> time(iterations);
   duration<double, std::nano> dur;
   double InsertionSort_time, MergeSort_time, noise;
   // for statistics;
   double mean, std_dev, sq_sum;
   std::vector<double> diff(iterations);
   // To measure algorithm complexity.
   size_t InsertionSort_comparison, MergeSort_comparison;

   // insertion sort.
   printf("Testing InsertionSort: \n");
   for (size_t i = 0; i < iterations; i++) {
      // get back the original arr for new iteration.
      target = target_copy;
      // timing the code
      auto t1 = high_resolution_clock::now();
      insertion_sort(target, 0, size - 1);
      auto t2 = high_resolution_clock::now();
      dur = t2 - t1;
      time[i] = dur.count();
   }
   // Measure comparison.
   target = target_copy;
   InsertionSort_comparison = insertion_sort(target, 0, size - 1);

   // Statistics calculation.
   mean = std::accumulate(time.begin(), time.end(), 0.0) / iterations;
   // get diff[i] = time[i] - mean, utilizing parallel execution.
   std::transform(time.begin(), time.end(), diff.begin(),
                  [mean](double x) { return x - mean; });
   // get the sum square of diff, careful for overflow.
   sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   std_dev = std::sqrt(sq_sum / iterations);

   // Out put the result.
   InsertionSort_time = mean, noise = std_dev;
   printf("%.1f +- %.2f nanoseconds over %d runs\nNumber of comparison: %d\n",
          InsertionSort_time, noise, iterations, InsertionSort_comparison);

   // Do again for MergeSort.
   printf("Testing MergeSort: \n");
   for (size_t i = 0; i < iterations; i++) {
      target = target_copy;
      auto t1 = high_resolution_clock::now();
      merge_sort(target, 0, size - 1);
      auto t2 = high_resolution_clock::now();
      dur = t2 - t1;
      time[i] = dur.count();
   }
   // Measure comparison.
   target = target_copy;
   MergeSort_comparison = merge_sort(target, 0, size - 1);

   mean = std::accumulate(time.begin(), time.end(), 0.0) / iterations;
   std::transform(time.begin(), time.end(), diff.begin(),
                  [mean](double x) { return x - mean; });
   sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   std_dev = std::sqrt(sq_sum / iterations);

   MergeSort_time = mean, noise = std_dev;
   printf("%.1f +- %.2f nanoseconds over %d runs.\n Number of comparison: %d\n",
          MergeSort_time, noise, iterations, MergeSort_comparison);

   return;
}
//////////////////////////

int main() {
   size_t size, threshold, iters;
   std::cout << "Enter arr size, threshold value (S) and number of "
                "iterations for benmark: \n";
   std::cin >> size >> threshold >> iters;
   std::vector<int> test_1 = test1(size);
   std::vector<int> test_2 = test2(size);
   std::vector<int> test_3 = test3(size);
   std::vector<int> test_4 = test4(size);

   ///// TESTING THE CLOCK /////////////
   // std::vector<int> test_2_copy = test_2;
   // int iter = 10;
   // std::vector<double> time(iter);
   // for (int i = 0; i < iter; i++) {
   //    auto t1 = high_resolution_clock::now();
   //    hybrid_sort(test_2, 0, size - 1, threshold);
   //    auto t2 = high_resolution_clock::now();
   //    duration<double, std::nano> dur = t2 - t1;
   //    time[i] = dur.count();
   //    test_2 = test_2_copy;
   // }
   // double average_time = std::accumulate(time.begin(), time.end(), 0.0) /
   // iter; std::cout << average_time << " nanoseconds\n";
   ////////////////////////////////////

   /// HYBRID VS MERGE /////////////
   // std::cout << "\nTest 1 (reversed array): \n\n";
   // benchmark_hybrid_merge(test_1, size, threshold, iters);
   // std::cout << "\nTest 2 (randomized array): \n\n";
   // benchmark_hybrid_merge(test_2, size, threshold, iters);
   // std::cout << "\nTest 3 (uniform array): \n\n";
   // benchmark_hybrid_merge(test_3, size, threshold, iters);
   // std::cout << "\nTest 4 (sorted array):  \n\n";
   // benchmark_hybrid_merge(test_4, size, threshold, iters);
   /////////////////////////////////

   ///// INSERTION VS MERGE /////////////
   std::cout << "\nTest 2 (randomized array): \n\n";
   benchmark_insertion_vs_merge(test_2, size, iters);
   /////////////////////////////////////

   return 0;
}

// Gcc installation guide: https://code.visualstudio.com/docs/cpp/config-mingw
// Install Vscode, MS C/C++ extension and Code Runner extension.

// References:
// [1] https://stackoverflow.com/a/7616783/15084416 (calculate std)
// [2] https://en.cppreference.com/w/cpp/algorithm/transform_reduce
// [3] https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag
// [4] https://en.cppreference.com/w/cpp/algorithm/transform
// [5] https://stackoverflow.com/a/22387757/15084416