// Created by Melissa Gries (CadenEras) on 5/23/2022.
#include "MovePlayer.h"

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <windows.h>

#define SCREEN_WIDTH    20
#define SCREEN_HEIGHT   15
#define START_X         0
#define START_Y         7

#define PLAYER '@'
#define WALL '#'

void CreateMaze(CHAR_INFO screenBuffer[], int playerX, int playerY);

BOOL MovePlayer(CHAR_INFO screenBuffer[], COORD *playerPos);

void main() {
    CHAR_INFO screenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    COORD playerPos = {START_X, START_Y};
    int x = 0, y = 0;

    srand(GetTickCount());

    for (y = 0; y < bufferSize.Y; y++) {
        for (x = 2; x < bufferSize.X; x++) {
            if (!(rand() % 3)){
                screenBuffer[x + y * SCREEN_WIDTH].Char.AsciiChar = WALL;
                screenBuffer[x + y * SCREEN_HEIGHT].Attributes = FOREGROUND_GREEN;
            }
        }
    }

    CreateMaze(screenBuffer, playerPos.X, playerPos.Y);

    while (1) {
        if (MovePlayer(screenBuffer, &playerPos)) {
            CreateMaze(screenBuffer, playerPos.X, playerPos.Y);
        }
    }
}

void CreateMaze(CHAR_INFO screenBuffer[], int playerX, int playerY) {
    SMALL_RECT drawRect = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    COORD writeFrom = {0, 0};
    HANDLE hOutput;

    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    screenBuffer[playerX + playerY * SCREEN_WIDTH].Char.AsciiChar = PLAYER;
    screenBuffer[playerX + playerY * SCREEN_HEIGHT].Attributes = FOREGROUND_RED;

    WriteConsoleOutput(hOutput, screenBuffer, bufferSize, writeFrom, &drawRect);
}

BOOL MovePlayer(CHAR_INFO screenBuffer[], COORD *playerPos) {
    INPUT_RECORD InputRecord;
    COORD oldPosition = *playerPos;
    DWORD Events=0;
    HANDLE hInput;
    BOOL bPlayerMoved = FALSE;
    int bKeyDown = 0;

    hInput = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleInput(hInput, &InputRecord, 1, &Events);

    bKeyDown = InputRecord.Event.KeyEvent.bKeyDown;

    if(InputRecord.EventType == KEY_EVENT && bKeyDown) {
        if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
            if (playerPos ->X < (SCREEN_WIDTH - 1)) {
                playerPos->X++;
                bPlayerMoved = TRUE;
            }
        } else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
            if (playerPos->X > 0) {
                playerPos->X++;
                bPlayerMoved = TRUE;
            }
        } else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP) {
            if (playerPos->Y > 0) {
                playerPos->Y--;
                bPlayerMoved = TRUE;
            }
        } else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
            if (playerPos->Y < (SCREEN_HEIGHT - 1)) {
                playerPos->Y++;
                bPlayerMoved = TRUE;
            }
        } else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
            exit(0);
        }
    }

    FlushConsoleInputBuffer(hInput);

    if (bPlayerMoved) {
        if (screenBuffer[playerPos->X + playerPos->Y * SCREEN_WIDTH].Char.AsciiChar != WALL) {
            screenBuffer[oldPosition.X + oldPosition.Y * SCREEN_WIDTH].Char.AsciiChar = ' ';
            screenBuffer[oldPosition.X + oldPosition.Y * SCREEN_HEIGHT].Attributes = 0;
        } else {
            *playerPos = oldPosition;
        }
        return TRUE;
    }
    return TRUE;
}

/*struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph {
    int numVertices;
    //To store a two-dimensional array
    int* visited;
    struct node** adjLists;
};

//Starting DFS algo
void DFS(struct Graph* graph, int vertex) {
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

//Creating a node
struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct Graph));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

//Create de graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; ++i) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

//add edge
void addEdge(struct Graph* graph, int src, int dest) {
    //add edge from source to destination
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    //add edge from destination to source
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

//print the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    struct Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    printGraph(graph);

    DFS(graph, 2);

    return 0;
}*/