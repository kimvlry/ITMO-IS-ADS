#include <iostream>
#include <vector>

using namespace std;


void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited) {
	visited[v] = true;
	for (const auto& it : graph[v]) {
		if (!visited[it]) {
			DFS(it, graph, visited);
		}
	}
}


int CountComponents(vector<vector<int>>& graph) {
	vector<bool> visited;
	visited.assign(graph.size(), false);
	int components = 0;
	for (int i = 0; i < graph.size(); ++i) {
		if (!visited[i]) {
			++components;
			DFS(i, graph, visited);
		}
	}
	return components;
}


int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph;
	graph.assign(n, {});

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout << CountComponents(graph);
}
