#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int INF = 1e9;

// -------------------------------------------------------------
// 1. GRAPH (Adjacency List + Matrix)
// -------------------------------------------------------------
class Graph {
public:
    int n;
    vector<vector<pair<int,int>>> adj;  // adjacency list
    vector<vector<int>> mat;            // adjacency matrix

    Graph(int size = 20) {
        n = 0;
        mat = vector<vector<int>>(size, vector<int>(size, INF));
        adj = vector<vector<pair<int,int>>>(size);
    }

    void addNode() {
        n++;
        mat[n][n] = 0;
        cout << "Node " << n << " added.\n";
    }

    void addEdge(int u, int v, int w, bool directed) {
        if (u > n || v > n) {
            cout << "Invalid node.\n";
            return;
        }
        adj[u].push_back({v, w});
        mat[u][v] = w;

        if (!directed) {
            adj[v].push_back({u, w});
            mat[v][u] = w;
        }

        cout << "Edge added.\n";
    }

    void printList() {
        cout << "Adjacency List:\n";
        for (int i = 1; i <= n; i++) {
            cout << i << ": ";
            for (auto p : adj[i]) {
                cout << "(" << p.first << "," << p.second << ") ";
            }
            cout << endl;
        }
    }

    void printMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (mat[i][j] == INF) cout << "INF ";
                else cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    // ---------------------------------------------------------
    // 2. DIJKSTRA
    // ---------------------------------------------------------
    void dijkstra(int start) {
        vector<int> dist(n+1, INF);
        dist[start] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d != dist[u]) continue;

            for (auto p : adj[u]) {
                int v = p.first;
                int w = p.second;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra distances from " << start << ":\n";
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INF) cout << "INF ";
            else cout << dist[i] << " ";
        }
        cout << endl;
    }

    // ---------------------------------------------------------
    // 3. FLOYD WARSHALL
    // ---------------------------------------------------------
    void floydWarshall() {
        vector<vector<int>> d = mat;

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] < INF && d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

        cout << "Floyd Warshall matrix:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][j] == INF) cout << "INF ";
                else cout << d[i][j] << " ";
            }
            cout << endl;
        }
    }

    // ---------------------------------------------------------
    // 4. TOPOLOGICAL SORT (KAHN)
    // ---------------------------------------------------------
    void topoSort() {
        vector<int> indeg(n+1, 0);

        for (int u = 1; u <= n; u++)
            for (auto p : adj[u])
                indeg[p.first]++;

        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (indeg[i] == 0) q.push(i);

        vector<int> order;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);

            for (auto p : adj[u]) {
                int v = p.first;
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }

        if (order.size() != n) {
            cout << "Cycle detected. Topological sort not possible.\n";
            return;
        }

        cout << "Topological Order: ";
        for (int x : order) cout << x << " ";
        cout << endl;
    }

    // ---------------------------------------------------------
    // 5. PRIM’S MST
    // ---------------------------------------------------------
    void primMST() {
        vector<int> key(n+1, INF);
        vector<bool> used(n+1, false);

        key[1] = 0;
        int total = 0;

        for (int i = 1; i <= n; i++) {
            int u = -1;
            for (int j = 1; j <= n; j++)
                if (!used[j] && (u == -1 || key[j] < key[u]))
                    u = j;

            used[u] = true;
            total += key[u];

            for (auto p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if (!used[v] && w < key[v])
                    key[v] = w;
            }
        }

        cout << "MST Cost: " << total << endl;
    }
};

// -------------------------------------------------------------
// 6. SIMPLE BINARY TREE FOR CITY ZONES
// -------------------------------------------------------------
struct Node {
    string zone;
    Node* left;
    Node* right;
    Node(string z) { zone = z; left = right = NULL; }
};

Node* insertZone(Node* root, string z) {
    if (root == NULL) return new Node(z);

    if (z < root->zone) root->left = insertZone(root->left, z);
    else root->right = insertZone(root->right, z);

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->zone << endl;
    inorder(root->right);
}

// -------------------------------------------------------------
// MAIN MENU
// -------------------------------------------------------------
int main() {
    Graph G;
    Node* zoneRoot = NULL;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Node\n";
        cout << "2. Add Edge\n";
        cout << "3. Print Adjacency List\n";
        cout << "4. Print Adjacency Matrix\n";
        cout << "5. Dijkstra\n";
        cout << "6. Floyd Warshall\n";
        cout << "7. Insert Zone\n";
        cout << "8. Display Zones\n";
        cout << "9. Topological Sort\n";
        cout << "10. Prim MST\n";
        cout << "0. Exit\n";

        int ch;
        cin >> ch;

        if (ch == 0) break;

        if (ch == 1) {
            G.addNode();
        }
        else if (ch == 2) {
            int u, v, w, d;
            cout << "Enter u v weight: ";
            cin >> u >> v >> w;
            cout << "Directed? (1=yes 0=no): ";
            cin >> d;
            G.addEdge(u, v, w, d == 1);
        }
        else if (ch == 3) G.printList();
        else if (ch == 4) G.printMatrix();
        else if (ch == 5) {
            int s; cout << "Start: "; cin >> s;
            G.dijkstra(s);
        }
        else if (ch == 6) G.floydWarshall();
        else if (ch == 7) {
            string z; 
            cout << "Zone name: ";
            cin >> z;
            zoneRoot = insertZone(zoneRoot, z);
        }
        else if (ch == 8) inorder(zoneRoot);
        else if (ch == 9) G.topoSort();
        else if (ch == 10) G.primMST();
        else cout << "Invalid.\n";
    }

    return 0;
}
