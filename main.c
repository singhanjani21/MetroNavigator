#include "metro.h"

int main(void) {
    MetroGraph* metro = create_graph();

    // Populate network lines and connections
    add_edge(metro, "Chandni_Chowk", "New_Delhi", 2, "Yellow");
    add_edge(metro, "New_Delhi", "Rajiv_Chowk", 2, "Yellow");
    add_edge(metro, "Rajiv_Chowk", "Mandi_House", 4, "Blue");
    add_edge(metro, "Mandi_House", "Botanical_Garden", 22, "Blue");

    // Execute test query
    find_shortest_path(metro, "Chandni_Chowk", "Botanical_Garden");

    // Clean up memory
    free_graph(metro);
    return 0;
}