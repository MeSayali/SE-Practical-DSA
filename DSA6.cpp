#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Graph {
public:
    Node* G[20];
    bool visited[20];
    int vertices;

    Graph(int n) {
        vertices = n;
        for (int i = 0; i < n; i++) {
            G[i] = new Node(i);
            visited[i] = false;
        }
    }

    void create(int edges) {
        int s, d;
        for (int i = 0; i < edges; i++) {
            cout << "Enter Source and Destination: ";
            cin >> s >> d;

            Node* temp = G[s];
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = new Node(d);

            temp = G[d];
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = new Node(s);
        }
    }

    void DFS(int v) {
        cout << v << " ";
        visited[v] = true;
        Node* temp = G[v]->next;
        while (temp != NULL) {
            if (!visited[temp->data])
                DFS(temp->data);
            temp = temp->next;
        }
    }

    void BFS(int start) {
        bool visitedBFS[vertices] = {false};
        queue<int> q;
        q.push(start);
        visitedBFS[start] = true;

        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";
            q.pop();

            Node* temp = G[v]->next;
            while (temp != NULL) {
                if (!visitedBFS[temp->data]) {
                    q.push(temp->data);
                    visitedBFS[temp->data] = true;
                }
                temp = temp->next;
            }
        }
    }

    void resetVisited() {
        for (int i = 0; i < vertices; i++)
            visited[i] = false;
    }
};

int main() {
    int n, edges, start;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g(n);
    g.create(edges);

    cout << "Enter Starting Node for DFS: ";
    cin >> start;
    cout << "DFS Traversal: ";
    g.DFS(start);
    cout << endl;

    g.resetVisited();
    cout << "Enter Starting Node for BFS: ";
    cin >> start;
    cout << "BFS Traversal: ";
    g.BFS(start);
    cout << endl;

    return 0;
}
