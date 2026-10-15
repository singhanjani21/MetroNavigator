# 🚇 Graph-Based Metro Transit Navigator & Route Optimization Engine

A high-performance command-line transit routing system built in **pure C** (C99), leveraging custom graph data structures and an optimized Priority Queue to compute shortest paths and detect line interchanges.

## 🚀 Features
* **Custom Adjacency List Graph:** Efficiently models sparse urban transit networks ($O(V + E)$ space complexity).
* **Indexed Binary Min-Heap:** Custom-built priority queue featuring an auxiliary position lookup array (`pos[]`), optimizing Dijkstra's `decrease_key` operation to $O(\log V)$.
* **Line Interchange Detection:** Automatically tracks line switches during path reconstruction and prints step-by-step commuter instructions.
* **Strict Memory Safety:** Explicit dynamic memory deallocation verified with **Valgrind** (0 memory leaks).

---

## 📊 Algorithmic Complexity

| Component | Traditional Approach | Engineered Implementation |
| :--- | :--- | :--- |
| **Graph Storage** | Adjacency Matrix: $O(V^2)$ | Adjacency List: **$O(V + E)$** |
| **Extract Min** | Linear Scan: $O(V)$ | Binary Min-Heap: **$O(\log V)$** |
| **Decrease-Key** | Linear Scan: $O(V)$ | Auxiliary Index (`pos[]`): **$O(1)$ lookup** |
| **Total Query Runtime** | $O(V^2)$ | **$O((V + E) \log V)$** |

---

## 🛠️ Project Structure
```text
metro_navigator/
├── metro.h        # Shared macros, structs, and function prototypes
├── graph.c        # Dynamic station mapping and adjacency list construction
├── heap.c         # Indexed binary min-heap and decrease-key logic
├── dijkstra.c     # Shortest path solver and line-change path reconstructor
├── main.c         # Network initialization and CLI entry point
