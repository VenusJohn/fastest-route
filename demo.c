#include <stdio.h>

#define N 6
#define INF 999999

char *places[N] = {
    "Main Gate",
    "Library",
    "CSE Block",
    "Canteen",
    "Computer Lab",
    "Admin Block"
};

/* Distance between locations in metres */
int graph[N][N] = {
    {0, 100, 0,   0,   0, 120},
    {100, 0, 80,  0, 100, 0},
    {0, 80, 0, 150,   0, 0},
    {0, 0, 150,  0,  70, 0},
    {0, 100, 0, 70,   0, 90},
    {120, 0, 0,  0,  90, 0}
};

void showPlaces() {
    int i;

    printf("\n========== CAMPUS LOCATIONS ==========\n");

    for (i = 0; i < N; i++) {
        printf("%d. %s\n", i, places[i]);
    }
}

int bfs(int start, int end, int path[]) {
    int visited[N] = {0};
    int parent[N];
    int queue[N];
    int front = 0, rear = 0;
    int i, current, count = 0;

    for (i = 0; i < N; i++)
        parent[i] = -1;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        current = queue[front++];

        if (current == end)
            break;

        for (i = 0; i < N; i++) {
            if (graph[current][i] > 0 &&
                !visited[i]) {
                visited[i] = 1;
                parent[i] = current;
                queue[rear++] = i;
            }
        }
    }

    if (!visited[end])
        return -1;

    current = end;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    for (i = 0; i < count / 2; i++) {
        int temp = path[i];
        path[i] = path[count - 1 - i];
        path[count - 1 - i] = temp;
    }

    return count;
}

int dijkstra(int start, int end, int path[]) {
    int dist[N], visited[N] = {0};
    int parent[N];
    int i, j, u, min;
    int count = 0;

    for (i = 0; i < N; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (i = 0; i < N; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < N; j++) {
            if (graph[u][j] > 0 &&
                !visited[j] &&
                dist[u] + graph[u][j] < dist[j]) {

                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }

    if (dist[end] == INF)
        return -1;

    i = end;

    while (i != -1) {
        path[count++] = i;
        i = parent[i];
    }

    for (i = 0; i < count / 2; i++) {
        int temp = path[i];
        path[i] = path[count - 1 - i];
        path[count - 1 - i] = temp;
    }

    return dist[end];
}

int calculateDistance(int path[], int count) {
    int i, distance = 0;

    for (i = 0; i < count - 1; i++) {
        distance += graph[path[i]][path[i + 1]];
    }

    return distance;
}

void displayRoute(int path[], int count) {
    int i;

    for (i = 0; i < count; i++) {
        printf("%s", places[path[i]]);

        if (i < count - 1)
            printf(" -> ");
    }

    printf("\n");
}

void findRoutes(int start, int end) {
    int bfsPath[N], shortestPath[N];
    int bfsCount, shortestDistance;
    int bfsDistance;

    bfsCount = bfs(start, end, bfsPath);
    shortestDistance = dijkstra(start, end, shortestPath);

    if (bfsCount == -1 || shortestDistance == -1) {
        printf("\nNo route exists between these locations.\n");
        return;
    }

    bfsDistance = calculateDistance(bfsPath, bfsCount);

    printf("\n========== ROUTE RESULTS ==========\n");

    printf("\nBFS ROUTE (Fewest Road Connections)\n");
    displayRoute(bfsPath, bfsCount);
    printf("Road connections: %d\n", bfsCount - 1);
    printf("Route distance: %d metres\n", bfsDistance);

    printf("\nDIJKSTRA ROUTE (Shortest Distance)\n");
    displayRoute(shortestPath,
                 bfs(start, end, bfsPath));
    printf("Total distance: %d metres\n", shortestDistance);

    printf("\n========== ROUTE ANALYSIS ==========\n");

    if (bfsDistance == shortestDistance) {
        printf("Both routes have the same distance.\n");
    } else if (bfsDistance > shortestDistance) {
        printf("Distance saved: %d metres\n",
               bfsDistance - shortestDistance);
    } else {
        printf("BFS route has fewer road connections.\n");
        printf("Dijkstra route has the shortest distance.\n");
    }
}

int main() {
    int choice, start, end;

    do {
        printf("\n====================================\n");
        printf("   SMART CAMPUS ROUTE FINDER\n");
        printf("====================================\n");
        printf("1. Display Campus Locations\n");
        printf("2. Find Route and Compare Algorithms\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            return 0;
        }

        switch (choice) {
            case 1:
                showPlaces();
                break;

            case 2:
                showPlaces();

                printf("\nEnter starting location ID: ");
                if (scanf("%d", &start) != 1) {
                    printf("Invalid input.\n");
                    return 0;
                }

                printf("Enter destination location ID: ");
                if (scanf("%d", &end) != 1) {
                    printf("Invalid input.\n");
                    return 0;
                }

                if (start < 0 || start >= N ||
                    end < 0 || end >= N) {
                    printf("Invalid location ID!\n");
                } else {
                    findRoutes(start, end);
                }
                break;

            case 3:
                printf("Thank you for using Smart Campus Route Finder!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}