#include "metro.h"

MetroGraph* create_graph(void) {
    MetroGraph* graph = (MetroGraph*)malloc(sizeof(MetroGraph));
    graph->num_stations = 0;
    for (int i = 0; i < MAX_STATIONS; i++) {
        graph->stations[i].head = NULL;
        graph->stations[i].name[0] = '\0';
    }
    return graph;
}

int get_or_add_station(MetroGraph* graph, const char* name) {
    for (int i = 0; i < graph->num_stations; i++) {
        if (strcmp(graph->stations[i].name, name) == 0) {
            return i;
        }
    }
    int id = graph->num_stations++;
    strncpy(graph->stations[id].name, name, MAX_NAME_LEN - 1);
    graph->stations[id].name[MAX_NAME_LEN - 1] = '\0';
    return id;
}

void add_edge(MetroGraph* graph, const char* src_name, const char* dest_name, int weight, const char* line) {
    int u = get_or_add_station(graph, src_name);
    int v = get_or_add_station(graph, dest_name);

    // Edge u -> v
    AdjListNode* node_v = (AdjListNode*)malloc(sizeof(AdjListNode));
    node_v->dest = v;
    node_v->weight = weight;
    strncpy(node_v->line, line, MAX_LINE_LEN - 1);
    node_v->line[MAX_LINE_LEN - 1] = '\0';
    node_v->next = graph->stations[u].head;
    graph->stations[u].head = node_v;

    // Edge v -> u
    AdjListNode* node_u = (AdjListNode*)malloc(sizeof(AdjListNode));
    node_u->dest = u;
    node_u->weight = weight;
    strncpy(node_u->line, line, MAX_LINE_LEN - 1);
    node_u->line[MAX_LINE_LEN - 1] = '\0';
    node_u->next = graph->stations[v].head;
    graph->stations[v].head = node_u;
}

void free_graph(MetroGraph* graph) {
    for (int i = 0; i < graph->num_stations; i++) {
        AdjListNode* curr = graph->stations[i].head;
        while (curr) {
            AdjListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
}