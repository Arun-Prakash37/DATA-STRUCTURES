#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int numVertices;
    int** adjacencyMatrix;
    int* visited;
} Graph;

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->visited = (int*)calloc(numVertices, sizeof(int));
    graph->adjacencyMatrix = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
}

void DFSUtil(Graph* graph, int vertex, int* stack) {
    graph->visited[vertex] = 1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] && !graph->visited[i]) {
            DFSUtil(graph, i, stack);
        }
    }
    stack[--(*stack)] = vertex;
}

void topologicalSort(Graph* graph) {
    int stack[MAX_VERTICES];
    int top = graph->numVertices;
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            DFSUtil(graph, i, &top);
        }
    }
    printf("Topological sorting order: ");
    for (int i = top; i < graph->numVertices; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph->visited);
    free(graph);
}

int main() {
    int numVertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    Graph* graph = createGraph(numVertices);
    printf("Enter the edges (src dest): \n");
    while (1) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        if (src == -1 || dest == -1)
            break;
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            printf("Invalid edge: (%d, %d)\n", src, dest);
            continue;
        }
        addEdge(graph, src, dest);
    }

    topologicalSort(graph);

    freeGraph(graph);
    return 0;
}
