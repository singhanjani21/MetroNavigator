#ifndef METRO_H
#define METRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_STATIONS 100
#define MAX_NAME_LEN 64
#define MAX_LINE_LEN 32

typedef struct AdjListNode {
    int dest;
    int weight; // Travel time in minutes
    char line[MAX_LINE_LEN];
    struct AdjListNode* next;
} AdjListNode;

typedef struct Station {
    char name[MAX_NAME_LEN];
    AdjListNode* head;
} Station;

typedef struct MetroGraph {
    int num_stations;
    Station stations[MAX_STATIONS];
} MetroGraph;

typedef struct HeapNode {
    int v;
    int dist;
} HeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos; // pos[v] stores heap array index for station v (O(1) decrease-key)
    HeapNode** array;
} MinHeap;

// Function Prototypes
MetroGraph* create_graph(void);
int get_or_add_station(MetroGraph* graph, const char* name);
void add_edge(MetroGraph* graph, const char* src_name, const char* dest_name, int weight, const char* line);
void free_graph(MetroGraph* graph);

HeapNode* new_heap_node(int v, int dist);
MinHeap* create_min_heap(int capacity);
void min_heapify(MinHeap* min_heap, int idx);
HeapNode* extract_min(MinHeap* min_heap);
void decrease_key(MinHeap* min_heap, int v, int dist);
int is_in_min_heap(MinHeap* min_heap, int v);
void free_min_heap(MinHeap* min_heap);

const char* get_connecting_line(MetroGraph* graph, int u, int v);
void print_itinerary(MetroGraph* graph, int* parent, int dest_id, int src_id, int total_time);
void find_shortest_path(MetroGraph* graph, const char* src_name, const char* dest_name);

#endif // METRO_H