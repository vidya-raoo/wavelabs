#include <iostream>
#include <vector>

using namespace std;

void dfs(int node, int parent, int& time, vector<vector<int>>& graph, vector<int>& discovery, vector<int>& low, vector<vector<int>>& criticalConnections) {
    discovery[node] = low[node] = ++time;

    for (int neighbor : graph[node]) {
        if (neighbor == parent)
            continue;

        if (discovery[neighbor] == 0) {
            dfs(neighbor, node, time, graph, discovery, low, criticalConnections);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] > discovery[node])
                criticalConnections.push_back({node, neighbor});
        }
        else {
            low[node] = min(low[node], discovery[neighbor]);
        }
    }
}

vector<vector<int>> findCriticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    vector<int> discovery(n, 0);
    vector<int> low(n, 0);
    vector<vector<int>> criticalConnections;

    for (auto& connection : connections) {
        int node1 = connection[0];
        int node2 = connection[1];
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    int time = 0;
    dfs(0, -1, time, graph, discovery, low, criticalConnections);

    return criticalConnections;
}

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};

    vector<vector<int>> criticalConnections = findCriticalConnections(n, connections);

    cout << "Critical Connections:\n";
    for (auto& connection : criticalConnections) {
        cout << connection[0] << " - " << connection[1] << endl;
    }

    return 0;
}