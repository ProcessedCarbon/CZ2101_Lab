#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <random>
#include <vector>

// benchmarking the codes.
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
// typedef for convenience.
using u32 = uint32_t;  // unsigned 32 bits int.
using u64 = uint64_t;  // unsigned 32 bits int.
using ll = long long;  // 64 bits int.
#define inf = INFINITY;

// Graph structure.
typedef struct _graph {
   size_t V;
   size_t E;
   std::vector<std::vector<size_t>> matrix;
   std::vector<std::list<size_t>> list;
} Graph;

u64 dijkstra_part_a(Graph& g, size_t source);
u64 dijkstra_part_b(Graph& g, size_t source);
Graph random_graph(size_t V, size_t E);
Graph random_tree(size_t V);
void print_graph(Graph& g);

int main() {
   std::vector<size_t> a(32, 10);
   for (int i = 0; i < a.size(); i++) {
      a[i] = i;
   }

   std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(a.begin(), a.end(), g);

   // std::make_heap(a.begin(), a.end(), std::greater<>());
   for (auto i : a) {
      std::cout << i << " ";
   }
   return 0;
}
