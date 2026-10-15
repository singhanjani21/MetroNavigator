#include "metro.h"

const char* get_connecting_line(MetroGraph* graph, int u, int v) {
    AdjListNode* curr = graph->stations[u].head;
    while (curr) {
        if (curr->dest == v) return curr->line;
        curr = curr->next;
    }
    return "Unknown";
}

void print_itinerary(MetroGraph* graph, int* parent, int dest_id, int src_id, int total_time) {
    if (parent[dest_id] == -1 && dest_id != src_id) {
        printf("\nNo route exists between the selected stations.\n");
        return;
    }

    int path[MAX_STATIONS];
    int count = 0;
    int curr = dest_id;

    while (curr != -1) {
        path[count++] = curr;
        curr = parent[curr];
    }

    printf("\n=======================================================\n");
    printf("                  OPTIMAL METRO ROUTE                 \n");
    printf("=======================================================\n");
    printf("Total Estimated Transit Time: %d mins\n", total_time);
    printf("Total Stops: %d\n", count - 1);
    printf("-------------------------------------------------------\n");

    const char* active_line = NULL;

    for (int i = count - 1; i >= 0; i--) {
        int u = path[i];

        if (i == count - 1) {
            int next_u = path[i - 1];
            active_line = get_connecting_line(graph, u, next_u);
            printf("[BOARD]      %s (Start on %s Line)\n", graph->stations[u].name, active_line);
        } else if (i == 0) {
            printf("[ARRIVE]     %s\n", graph->stations[u].name);
        } else {
            int next_u = path[i - 1];
            const char* next_line = get_connecting_line(graph, u, next_u);

            if (strcmp(active_line, next_line) != 0) {
                printf("[TRANSFER]   %s (Switch: %s Line -> %s Line)\n", 
                       graph->stations[u].name, active_line, next_line);
                active_line = next_line;
            } else {
                printf("  |          %s\n", graph->stations[u].name);
            }
        }
    }
    printf("=======================================================\n\n");
}

void find_shortest_path(MetroGraph* graph, const char* src_name, const char* dest_name) {
    int src_id = -1, dest_id = -1;

    for (int i = 0; i < graph->num_stations; i++) {
        if (strcmp(graph->stations[i].name, src_name) == 0) src_id = i;
        if (strcmp(graph->stations[i].name, dest_name) == 0) dest_id = i;
    }

    if (src_id == -1 || dest_id == -1) {
        printf("Error: One or both stations not found in the network.\n");
        return;
    }

    int V = graph->num_stations;
    int dist[MAX_STATIONS];
    int parent[MAX_STATIONS];

    MinHeap* min_heap = create_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        parent[v] = -1;
        min_heap->array[v] = new_heap_node(v, dist[v]);
        min_heap->pos[v] = v;
    }

    dist[src_id] = 0;
    decrease_key(min_heap, src_id, 0);
    min_heap->size = V;

    while (min_heap->size > 0) {
        HeapNode* min_node = extract_min(min_heap);
        int u = min_node->v;

        if (dist[u] == INT_MAX || u == dest_id) break;

        AdjListNode* edge = graph->stations[u].head;
        while (edge != NULL) {
            int v = edge->dest;
            if (is_in_min_heap(min_heap, v) && dist[u] + edge->weight < dist[v]) {
                dist[v] = dist[u] + edge->weight;
                parent[v] = u;
                decrease_key(min_heap, v, dist[v]);
            }
            edge = edge->next;
        }
    }

    print_itinerary(graph, parent, dest_id, src_id, dist[dest_id]);
    free_min_heap(min_heap);
}