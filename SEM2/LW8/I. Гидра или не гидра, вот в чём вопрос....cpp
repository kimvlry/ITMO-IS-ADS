#include <iostream>
#include <vector>

using namespace std;


void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, int& count_edges) {
	visited[v] = true;
	count_edges += graph[v].size();
	for (int it : graph[v]) {
		if (!visited[it]) {
			DFS(it, graph, visited, count_edges);
		}
	}
}


void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited) {
	visited[v] = true;
	for (int it : graph[v]) {
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
	vector<bool> visited;
	graph.assign(n, {});
	visited.assign(graph.size(), false);

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int edges = 0;
	DFS(0, graph, visited, edges);
	(edges / 2) == n && CountComponents(graph) == 1 ? cout << "ARCHIMEDES" : cout << "EUCLID";
}
