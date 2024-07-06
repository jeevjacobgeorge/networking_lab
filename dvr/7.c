#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODES 7 // Number of nodes (A, B, C, D, E, F, G)
#define INF INT_MAX

// Node indices: A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6
char *nodes[] = {"A", "B", "C", "D", "E", "F", "G"};

void print_routing_table(int dist[], int next_hop[]) {
    printf("Routing table for node B:\n");
    for (int i = 0; i < NODES; i++) {
        if (i != 1) { // Skip B itself
            printf("Shortest path to node %s: the next hop is %s and the cost is %.1f\n", nodes[i], nodes[next_hop[i]], (dist[i] == INF ? -1.0 : (double)dist[i]));
        }
    }
}

void distance_vector_routing(int graph[NODES][NODES]) {
    int dist[NODES];
    int next_hop[NODES];

    // Initialize distances and next hops
    for (int i = 0; i < NODES; i++) {
        dist[i] = graph[1][i]; // Start with direct distances from B
        if (graph[1][i] != INF && graph[1][i] != 0) {
            next_hop[i] = i; // Next hop is the node itself if directly connected
        } else {
            next_hop[i] = -1; // No next hop if not directly connected
        }
    }
    dist[1] = 0; // Distance to itself is 0
    next_hop[1] = 1; // Next hop to itself is itself

// Bellman-Ford algorithm
for (int k = 0; k < NODES - 1; k++) {
    for (int u = 0; u < NODES; u++) {
        for (int v = 0; v < NODES; v++) {
            // Check if there is an edge from u to v, and if u is reachable
            // and if the new calculated distance to v through u is shorter
            if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v]; // Update shortest distance to v
                next_hop[v] = next_hop[u]; // Update next hop for v
            }
        }
    }
}

    print_routing_table(dist, next_hop);
}

int main() {
    // Graph representation using adjacency matrix
    int graph[NODES][NODES] = {
        {0, 1, 1, INF, 1, 1, INF},  // A
        {1, 0, 1, INF, INF, INF, INF},  // B
        {1, 1, 0, 1, INF, INF, INF},  // C
        {INF, INF, 1, 0, INF, INF, 1},  // D
        {1, INF, INF, INF, 0, INF, INF},  // E
        {1, INF, INF, INF, INF, 0, 1},  // F
        {INF, INF, INF, 1, INF, 1, 0}   // G
    };

    distance_vector_routing(graph);
    return 0;
}
