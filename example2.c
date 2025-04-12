#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    int *visited;
    Node **adjLists;
} Graph;

typedef struct Queue
{
    int *items;
    int front;
    int rear;
} Queue;

Node *create_node(int vertex)
{
    Node *newNode = malloc(sizeof(Node));

    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
}

Graph *create_graph(int vertices)
{
    int i;

    Graph *graph = malloc(sizeof(Graph));

    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest)
{
    Node *newNode = create_node(dest);

    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void print_graph(Graph *graph)
{
    int i;

    for (i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjLists[i];

        printf("Nodul %d: ", i);

        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

void reset_visited(Graph *graph)
{
    int i;

    for (i = 0; i < graph->numVertices; i++)
    {
        graph->visited[i] = 0;
    }
}

Queue *create_queue(int size)
{
    Queue *queue = malloc(sizeof(Queue));

    queue->items = malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;

    return queue;
}

int is_queue_empty(Queue *queue)
{
    return queue->front == -1;
}

void enqueue(Queue *queue, int value)
{
    if (queue->rear == -1)
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear++;
    }
    queue->items[queue->rear] = value;
}

int dequeue(Queue *queue)
{
    int value = queue->items[queue->front];

    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front++;
    }
    return value;
}

void DFS(Graph *graph, int vertex)
{
    graph->visited[vertex] = 1;

    printf("%d ", vertex);

    Node *adjList = graph->adjLists[vertex];

    while (adjList)
    {
        int nextVertex = adjList->vertex;

        if (!graph->visited[nextVertex])
        {
            DFS(graph, nextVertex);
        }

        adjList = adjList->next;
    }
}

void BFS(Graph *graph, int startVertex)
{
    Queue *queue = create_queue(graph->numVertices);

    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!is_queue_empty(queue))
    {
        int currentVertex = dequeue(queue);

        printf("%d ", currentVertex);

        Node *temp = graph->adjLists[currentVertex];

        while (temp)
        {
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex])
            {
                graph->visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }

            temp = temp->next;
        }
    }

    free(queue->items);
    free(queue);
}

int main()
{
    int numVertices, numEdges, i, startVertex;;

    printf("Numarul de noduri in graf: ");
    scanf("%d", &numVertices);

    Graph *graph = create_graph(numVertices);

    printf("Numarul de muchii: ");
    scanf("%d", &numEdges);

    printf("Introduceti cele %d muchii (ex: 0 1):\n", numEdges);
    for (i = 0; i < numEdges; i++)
    {
        int src, dest;

        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    printf("\nReprezentarea grafului:\n");
    print_graph(graph);

    printf("\nStart DFS de la nodul: ");
    scanf("%d", &startVertex);
    
    printf("Parcurgere DFS: ");
    DFS(graph, startVertex);

    reset_visited(graph);

    printf("\n\nStart BFS de la nodul: ");
    scanf("%d", &startVertex);

    printf("Parcurgere BFS: ");
    BFS(graph, startVertex);

    printf("\n");

    return 0;
}
