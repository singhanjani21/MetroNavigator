#include "metro.h"

HeapNode* new_heap_node(int v, int dist) {
    HeapNode* node = (HeapNode*)malloc(sizeof(HeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

MinHeap* create_min_heap(int capacity) {
    MinHeap* min_heap = (MinHeap*)malloc(sizeof(MinHeap));
    min_heap->pos = (int*)malloc(capacity * sizeof(int));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = (HeapNode**)malloc(capacity * sizeof(HeapNode*));
    return min_heap;
}

void swap_heap_nodes(MinHeap* min_heap, int i, int j) {
    HeapNode* temp = min_heap->array[i];
    min_heap->array[i] = min_heap->array[j];
    min_heap->array[j] = temp;

    min_heap->pos[min_heap->array[i]->v] = i;
    min_heap->pos[min_heap->array[j]->v] = j;
}

void min_heapify(MinHeap* min_heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < min_heap->size && min_heap->array[left]->dist < min_heap->array[smallest]->dist)
        smallest = left;
    if (right < min_heap->size && min_heap->array[right]->dist < min_heap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        swap_heap_nodes(min_heap, idx, smallest);
        min_heapify(min_heap, smallest);
    }
}

HeapNode* extract_min(MinHeap* min_heap) {
    if (min_heap->size == 0) return NULL;

    HeapNode* root = min_heap->array[0];
    HeapNode* last_node = min_heap->array[min_heap->size - 1];

    min_heap->array[0] = last_node;
    min_heap->pos[root->v] = min_heap->size - 1;
    min_heap->pos[last_node->v] = 0;

    min_heap->size--;
    min_heapify(min_heap, 0);

    return root;
}

void decrease_key(MinHeap* min_heap, int v, int dist) {
    int i = min_heap->pos[v];
    min_heap->array[i]->dist = dist;

    while (i > 0 && min_heap->array[i]->dist < min_heap->array[(i - 1) / 2]->dist) {
        swap_heap_nodes(min_heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

int is_in_min_heap(MinHeap* min_heap, int v) {
    return min_heap->pos[v] < min_heap->size;
}

void free_min_heap(MinHeap* min_heap) {
    for (int i = 0; i < min_heap->capacity; i++) {
        free(min_heap->array[i]);
    }
    free(min_heap->array);
    free(min_heap->pos);
    free(min_heap);
}