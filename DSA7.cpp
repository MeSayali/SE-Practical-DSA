#include <iostream>
#include <climits>

using namespace std;

#define INF INT_MAX
#define MAX 100  // Maximum number of vertices

class Graph {
    int V;                // Number of vertices
    int adj[MAX][MAX];    // Adjacency matrix

public:
    Graph(int V) {
        this->V = V;

        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = INF;//at staring edge set to inf
    }

    void addEdge(int u, int v, int weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;  // Undirected graph
    }

    void primMST() {
        int key[MAX];       // Stores minimum weight edge for each vertex
        int parent[MAX];    // Stores the MST structure
        bool inMST[MAX];    // true if vertex is included in MST

        // Initialize all keys to inf and mark all vertices are ot included in inMST
        for (int i = 0; i < V; i++) {
            key[i] = INF;
            inMST[i] = false;
        }

        key[0] = 0;      // Start from vertex 0
        parent[0] = -1;  // first node has no parent

        for (int count = 0; count < V - 1; count++) {
            // Find the vertex with the minimum key value
            int minKey = INF, u = -1;

            for (int i = 0; i < V; i++)
                if (!inMST[i] && key[i] < minKey) {
                    minKey = key[i];
                    u = i;
                }

            inMST[u] = true;  // Include the chosen vertex in MST

            // Update key values and parent index of the adjacent vertices
            for (int v = 0; v < V; v++)
                if (adj[u][v] != INF && !inMST[v] && adj[u][v] < key[v]) {
                    key[v] = adj[u][v];
                    parent[v] = u;
                }
        }

        // Print the Minimum Spanning Tree
        int minCost = 0;
        cout << "Edges in Minimum Spanning Tree (Prim's Algorithm):\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " (" << key[i] << ")\n";
            minCost += key[i];
        }
        cout << "Total Minimum Cost: " << minCost << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges in the format (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    cout << "\nRunning Prim's Algorithm...\n";
    g.primMST();

    return 0;
}
