#include <iostream>
#include <vector>

using namespace std;


bool DFS(int v, int parent, vector<vector<int>>& graph, vector<bool>& visited) {
	visited[v] = true;
	for (const auto& it : graph[v]) {
		if (!visited[it]) {
			if (DFS(it, v, graph, visited)) {
				return true;
			}
		}
		else if (it != parent) {
			return true;
		}
	}
	return false;
}


bool IsCycled(vector<vector<int>>& graph) {
	vector<bool> visited(graph.size(), false);
	for (int i = 0; i < graph.size(); ++i) {
		if (!visited[i]) {
			if (DFS(i, -1, graph, visited)) {
				return true;
			}
		}
	}
	return false;
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

	IsCycled(graph) ? cout << "YES" : cout << "NO";
}
