#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int n = residualGraph.size();
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({ source, INT_MAX });

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v = 0; v < n; v++) {
            if (parent[v] == -1 && residualGraph[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, residualGraph[u][v]);
                if (v == sink)
                    return new_flow;
                q.push({ v, new_flow });
            }
        }
    }
    return 0;
}

int fordFulkerson(vector<vector<int>>& originalGraph, int source, int sink) {
    int n = originalGraph.size();
    vector<vector<int>> residualGraph = originalGraph;
    vector<int> parent(n, -1);
    int maxFlow = 0;

    while (true) {
        int flow = bfs(residualGraph, source, sink, parent);
        if (flow == 0)
            break;
        maxFlow += flow;
        int v = sink;
        while (v != source) {
            int u = parent[v];
            residualGraph[u][v] -= flow;
            residualGraph[v][u] += flow;
            v = u;
        }
    }

    // Looking for bottlenecks 
    cout << "Bottleneck edges:\n";
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (originalGraph[u][v] > 0 && residualGraph[u][v] == 0) {
                cout << "Edge " << u << " -> " << v << " is a bottleneck.\n";
            }
        }
    }

    return maxFlow;
}

void runExample(vector<vector<int>>& graph, int source, int sink, const string& exampleName) {
    cout << "\nRunning example: " << exampleName << "\n";
    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "Maximum RPS (flow): " << maxFlow << endl;
}

int main() {
    vector<vector<int>> graph1 = {
        {0, 20, 5, 0, 0},  // frontend -> auth_service, backup_service
        {0, 0, 0, 10, 0},  // auth_service -> database
        {0, 0, 0, 5, 0},   // backup_service -> database
        {0, 0, 0, 0, 30},  // database -> analytics
        {0, 0, 0, 0, 0}    // analytics
    };
    runExample(graph1, 0, 4, "Monolithic System with Bottleneck");

    vector<vector<int>> graph2 = {
        {0, 15, 15, 0, 0, 0},  // frontend -> service1, service2
        {0, 0, 0, 20, 0, 0},   // service1 -> database
        {0, 0, 0, 0, 20, 0},   // service2 -> cache
        {0, 0, 0, 0, 0, 30},   // database -> analytics
        {0, 0, 0, 0, 0, 30},   // cache -> analytics
        {0, 0, 0, 0, 0, 0}     // analytics
    };
    runExample(graph2, 0, 5, "Hybrid Architecture with Load Balancing");

    vector<vector<int>> graph3 = {
        {0, 20, 10, 0, 0, 0},  // frontend -> service1, service2
        {0, 0, 5, 15, 0, 0},   // service1 -> service2, database
        {0, 0, 0, 10, 0, 0},   // service2 -> database
        {0, 5, 0, 0, 25, 0},   // database -> service1, analytics
        {0, 0, 0, 0, 0, 30},   // analytics -> reporting
        {0, 0, 0, 0, 0, 0}     // reporting
    };

    runExample(graph3, 0, 5, "Complex System with Cyclic Dependencies");

    vector<vector<int>> graph4 = {
        {0, 25, 0, 0, 0, 0},  // frontend -> queue
        {0, 0, 15, 10, 0, 0}, // queue -> service1, service2
        {0, 0, 0, 0, 20, 0},  // service1 -> database
        {0, 0, 0, 0, 15, 0},  // service2 -> database
        {0, 0, 0, 0, 0, 30},  // database -> analytics
        {0, 0, 0, 0, 0, 0}    // analytics
    };

    runExample(graph4, 0, 5, "Asynchronous Processing with Queue");

    return 0;
}
