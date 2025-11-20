#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = 1e9;

/*---------------------------------------------
    BUILDING DATA NODE (BST / AVL)
----------------------------------------------*/
struct Building
{
    int id;
    string name;
    string location;
    Building *left, *right;
    int height;

    Building(int i, string n, string l)
    {
        id = i;
        name = n;
        location = l;
        left = right = NULL;
        height = 1;
    }
};

/*---------------------------------------------
    HEIGHT & BALANCE (AVL Helpers)
----------------------------------------------*/
int height(Building *n)
{
    return n ? n->height : 0;
}

int getBalance(Building *n)
{
    return n ? height(n->left) - height(n->right) : 0;
}

Building *rotateRight(Building *y)
{
    Building *x = y->left;
    Building *T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Building *rotateLeft(Building *x)
{
    Building *y = x->right;
    Building *T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

/*---------------------------------------------
    AVL INSERT
----------------------------------------------*/
Building *insertAVL(Building *root, int id, string name, string loc)
{
    if (!root)
        return new Building(id, name, loc);

    if (id < root->id)
        root->left = insertAVL(root->left, id, name, loc);
    else if (id > root->id)
        root->right = insertAVL(root->right, id, name, loc);
    else
        return root; // duplicates not allowed

    root->height = 1 + max(height(root->left), height(root->right));

    int bal = getBalance(root);

    // LL
    if (bal > 1 && id < root->left->id)
        return rotateRight(root);

    // RR
    if (bal < -1 && id > root->right->id)
        return rotateLeft(root);

    // LR
    if (bal > 1 && id > root->left->id)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if (bal < -1 && id < root->right->id)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

/*---------------------------------------------
    TREE TRAVERSALS
----------------------------------------------*/
void inorder(Building *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->id << " - " << root->name << " - " << root->location << endl;
    inorder(root->right);
}

void preorder(Building *root)
{
    if (!root)
        return;
    cout << root->id << " - " << root->name << " - " << root->location << endl;
    preorder(root->left);
    preorder(root->right);
}

void postorder(Building *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->id << " - " << root->name << " - " << root->location << endl;
}

/*---------------------------------------------
    GRAPH FOR CAMPUS PATHS
----------------------------------------------*/
class Graph
{
public:
    int n;
    vector<vector<pair<int, int>>> adj; // adjacency list
    vector<vector<int>> mat;            // adjacency matrix

    Graph(int size = 50)
    {
        n = 0;
        adj = vector<vector<pair<int, int>>>(size);
        mat = vector<vector<int>>(size, vector<int>(size, INF));
    }

    void addBuilding()
    {
        n++;
        mat[n][n] = 0;
        cout << "Building " << n << " added to graph.\n";
    }

    void addPath(int u, int v, int w)
    {
        if (u > n || v > n)
        {
            cout << "Invalid building ID.\n";
            return;
        }
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        mat[u][v] = mat[v][u] = w;
        cout << "Path added.\n";
    }

    void printMatrix()
    {
        cout << "Adjacency Matrix:\n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (mat[i][j] == INF)
                    cout << "INF ";
                else
                    cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    /*---------------------------------------------
        DIJKSTRA FOR OPTIMAL PATH
    ----------------------------------------------*/
    void dijkstra(int start)
    {
        vector<int> dist(n + 1, INF);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d != dist[u])
                continue;

            for (auto p : adj[u])
            {
                int v = p.first, w = p.second;
                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from " << start << ":\n";
        for (int i = 1; i <= n; i++)
            cout << "To " << i << " = " << dist[i] << endl;
    }

    /*---------------------------------------------
        KRUSKAL FOR UTILITY LAYOUT (MST)
    ----------------------------------------------*/
    void kruskalMST()
    {
        struct E
        {
            int u, v, w;
        };
        vector<E> edges;

        // Collect edges
        for (int u = 1; u <= n; u++)
        {
            for (auto p : adj[u])
            {
                int v = p.first, w = p.second;
                if (u < v)
                    edges.push_back({u, v, w});
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](E a, E b)
             { return a.w < b.w; });

        // DSU parent array
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        // Simple FIND function (no std::function)
        auto findSet = [&](int x)
        {
            while (parent[x] != x)
                x = parent[x];
            return x;
        };

        int total = 0;

        cout << "Kruskal MST:\n";

        // Build MST
        for (auto &e : edges)
        {
            int a = findSet(e.u);
            int b = findSet(e.v);

            if (a != b)
            {
                cout << e.u << " -- " << e.v << " : " << e.w << "\n";
                total += e.w;
                parent[a] = b;
            }
        }

        cout << "Total MST Cost: " << total << endl;
    }
};

/*---------------------------------------------
    EXPRESSION TREE (FOR ENERGY BILL EVALUATION)
----------------------------------------------*/
struct ExprNode
{
    char val;
    ExprNode *left, *right;
    ExprNode(char v)
    {
        val = v;
        left = right = NULL;
    }
};

class ExpressionTree
{
public:
    ExprNode *build(string postfix)
    {
        vector<ExprNode *> st;

        for (char c : postfix)
        {
            if (isdigit(c))
            {
                st.push_back(new ExprNode(c));
            }
            else
            {
                ExprNode *node = new ExprNode(c);
                node->right = st.back();
                st.pop_back();
                node->left = st.back();
                st.pop_back();
                st.push_back(node);
            }
        }
        return st.back();
    }

    int eval(ExprNode *root)
    {
        if (!root)
            return 0;
        if (isdigit(root->val))
            return root->val - '0';

        int l = eval(root->left);
        int r = eval(root->right);

        switch (root->val)
        {
        case '+':
            return l + r;
        case '-':
            return l - r;
        case '*':
            return l * r;
        case '/':
            return r ? l / r : 0;
        }
        return 0;
    }
};

/*---------------------------------------------
    MAIN SYSTEM
----------------------------------------------*/
int main()
{
    Building *root = NULL;
    Graph G;
    ExpressionTree ET;

    while (true)
    {
        cout << "\n--- Campus Navigation & Utility Planner ---\n";
        cout << "1. Add Building Record (AVL)\n";
        cout << "2. List Buildings - Inorder\n";
        cout << "3. List Buildings - Preorder\n";
        cout << "4. List Buildings - Postorder\n";
        cout << "5. Add Graph Building\n";
        cout << "6. Add Path\n";
        cout << "7. Print Adjacency Matrix\n";
        cout << "8. Find Optimal Path (Dijkstra)\n";
        cout << "9. Plan Utility Layout (Kruskal)\n";
        cout << "10. Evaluate Energy Bill (Expression Tree)\n";
        cout << "0. Exit\n";

        int ch;
        cin >> ch;

        if (ch == 0)
            break;

        if (ch == 1)
        {
            int id;
            string name, loc;
            cout << "ID: ";
            cin >> id;
            cout << "Building Name: ";
            cin >> name;
            cout << "Location: ";
            cin >> loc;

            root = insertAVL(root, id, name, loc);
            cout << "Inserted.\n";
        }

        else if (ch == 2)
            inorder(root);
        else if (ch == 3)
            preorder(root);
        else if (ch == 4)
            postorder(root);

        else if (ch == 5)
            G.addBuilding();
        else if (ch == 6)
        {
            int u, v, w;
            cout << "Enter u v weight: ";
            cin >> u >> v >> w;
            G.addPath(u, v, w);
        }

        else if (ch == 7)
            G.printMatrix();

        else if (ch == 8)
        {
            int start;
            cout << "Enter start building: ";
            cin >> start;
            G.dijkstra(start);
        }

        else if (ch == 9)
            G.kruskalMST();

        else if (ch == 10)
        {
            string postfix;
            cout << "Enter postfix expression: ";
            cin >> postfix;
            ExprNode *rootExp = ET.build(postfix);
            cout << "Result = " << ET.eval(rootExp) << endl;
        }
    }

    return 0;
}
