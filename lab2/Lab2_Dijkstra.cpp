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
using u32 = uint32_t;                   // unsigned 32 bits int.
using u64 = uint64_t;                   // unsigned 32 bits int.
using ll = long long;                   // 64 bits int.
#define inf ((float)(1e+300 * 1e+300))  // infinity.

// Graph structure.
typedef struct _graph {
   size_t V;
   size_t E;
   std::vector<std::vector<size_t>> matrix;
   std::vector<std::list<size_t>> list;
} Graph;

Graph random_graph(size_t V, size_t E);  // random directed connected graph.
void print_graph(Graph& g);  // print the graph in the form of an adj_list
u64 dijkstra_part_a(Graph& g, size_t source);  // part_a.
u64 dijkstra_part_b(Graph& g, size_t source);  // part_b.
void benchmark(Graph& g, size_t source);       // complexity and cpu runtime.

int main() {
   Graph g = random_graph(4, 7);

   for (int i = 0; i < g.matrix.size(); i++) {
      for (int j = 0; j < g.matrix[0].size(); j++) {
         printf("%-5d ", g.matrix[i][j]);
      }
      putchar('\n');
   }
   return 0;
}

// Generated a random directed and connnected graph. (make sure E>=V-1)
Graph random_graph(size_t V, size_t E) {
   // initialize the graph
   Graph g;
   g.V = V;
   g.E = 0;
   g.matrix = std::vector<std::vector<size_t>>(
       V, std::vector<size_t>(V, 0));  // empty matrix filled with 0.
   g.list = std::vector<std::list<size_t>>(
       V, std::list<size_t>());  // vector size V of empty lists.

   // If E < V-1, return an empty graph.
   if ((E < V - 1) || (E > (V * V - V))) {
      std::cout << "The number of edges is invalid, V^2-V >= E >= V-1 !"
                << std::endl;
      return g;
   }

   // create an array of vertex references (0 -> V-1) and shuffle it.
   std::vector<size_t> vertexes(V);
   for (size_t i = 0; i < vertexes.size(); i++) {
      vertexes[i] = i;
   }
   std::random_device rd;
   std::mt19937_64 rand_scheme(rd());
   std::shuffle(vertexes.begin() + 1, vertexes.end(), rand_scheme);

   // insert an undirected tree to make sure the graph is connnect.
   for (size_t i = 1; i < vertexes.size(); i++) {
      g.matrix[vertexes[i - 1]][vertexes[i]] = 1 + rand() % 1000;
      (g.E)++;
   }

   // randomly add vertexes until g.E == E. We try for atmost V^2 times,
   // otherwise the graph is nearly fully conntected. Our random scheme would
   // requires too much time.
   std::uniform_int_distribution<size_t> distr;
   size_t from, to, iters = 0;
   while (g.E < E && iters < V * V) {
      from = distr(rand_scheme) % V;
      to = 1 + distr(rand_scheme) % (V - 1);  // the to node of this edge
      if (g.matrix[from][to] == 0 && from != to) {
         std::cout << "from: " << from << " to: " << to << std::endl;
         g.matrix[from][to] = 1 + rand() % 1000;
         (g.E)++;
      }
      iters++;
   }

   // Sometimes, E ~ V^2, this make the random scheme infeasible. Then we need
   // to manually add edges in a deterministic way to meet the quota.
   for (from = 0; from < V; from++) {
      if (g.E == E) break;
      for (to = 1; to < V; to++) {
         if (from == to || g.matrix[from][to] != 0) continue;
         if (g.E == E) break;
         g.matrix[from][to] = 1 + rand() % 1000;
         (g.E)++;
      }
   }

   // Finally, get the adjacency list representation.
   for (size_t i = 0; i < V; i++) {
      for (size_t j = 0; j < V; j++) {
         if (g.matrix[i][j] != 0) {
            g.list[i].push_back(g.matrix[i][j]);
         }
      }
   }

   return g;
}

// dijkstra algorithm with priorityQ = array and graph = adj_list.
u64 dijkstra_part_a(Graph& g, size_t source) {
   u64 complexity = 0;
   return complexity;
}

// dijkstra algorithm with priorityQ = heap and graph = adj_matrix.
u64 dijkstra_part_b(Graph& g, size_t source) {
   u64 complexity = 0;
   return complexity;
}