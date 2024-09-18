#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int destination;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Structure to represent the graph
struct Graph {
    int numVertices;
    struct AdjList* list;
};

// Function to create a new node
struct Node* newNode(int destination) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->destination = destination;
    new->next = NULL;
    return new;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // Create an adjacency list for each vertex
    graph->list = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));

    // Initialize the adjacency lists as empty
    for (int i = 0; i < vertices; i++) {
        graph->list[i].head = NULL;
    }

    return graph;
}

// Function to add an edge (undirected graph)
void addEdge(struct Graph* graph, int origin, int destination) {
    // Add destination to the adjacency list of origin
    struct Node* new = newNode(destination);
    new->next = graph->list[origin].head;
    graph->list[origin].head = new;

    // Since the graph is undirected, add origin to the destination's list
    new = newNode(origin);
    new->next = graph->list[destination].head;
    graph->list[destination].head = new;
}

// Helper function to print the complete graph
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjacent = graph->list[i].head;
        printf("\n Vertex %d: ", i);
        while (adjacent) {
            printf(" -> %d", adjacent->destination);
            adjacent = adjacent->next;
        }
        printf("\n");
    }
}

// Helper function to perform Depth-First Search (DFS)
void depthFirstSearch(struct Graph* graph, int vertex, int* visited) {
    // Mark the vertex as visited
    visited[vertex] = 1;
    printf("Visiting %d \n", vertex);

    // Visit all unvisited adjacent vertices
    struct Node* adjacent = graph->list[vertex].head;
    while (adjacent != NULL) {
        if (!visited[adjacent->destination]) {
            depthFirstSearch(graph, adjacent->destination, visited);
        }
        adjacent = adjacent->next;
    }
}

int main() {
    // Number of vertices
    int V = 5;
    
    // Create the graph
    struct Graph* graph = createGraph(V);

    // Add the edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the complete graph
    printf("Complete graph:\n");
    printGraph(graph);

    // Perform Depth-First Search starting from vertex 0
    printf("\nDepth-First Search (DFS) starting from vertex 0:\n");
    int* visited = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    depthFirstSearch(graph, 0, visited);

    // Free memory
    free(visited);
    free(graph->list);
    free(graph);

    return 0;
}
