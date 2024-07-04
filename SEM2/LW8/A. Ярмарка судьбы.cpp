#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void DFS(int vertex, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& sorted) {
	visited[vertex] = true;
	for (const auto& it : graph[vertex]) {
		if (!visited[it]) {
			DFS(it, graph, visited, sorted);
		}
	}
	sorted.push_back(vertex);
}


void Topsort(vector<vector<int>>& graph, vector<bool>& visited, vector<int>& sorted) {
	for (int v = 0; v < graph.size(); ++v) {
		if (!visited[v]) {
			DFS(v, graph, visited, sorted);
		}
	}
	reverse(sorted.begin(), sorted.end());
}


int main() {
	int n, m, first_gift, second_gift;
	cin >> n >> m;

	vector<vector<int>> graph;
	vector<bool> visited;
	vector<int> sorted;
	vector<int> reorganized;

	graph.assign(n, {});
	visited.assign(n, false);
	reorganized.assign(n, 0);

	for (int i = 0; i < m; ++i) {
		cin >> first_gift >> second_gift;
		graph[first_gift - 1].push_back(second_gift - 1);
	}

	Topsort(graph, visited, sorted);

	for (int i = 0; i < n; ++i) {
		reorganized[sorted[i]] = i + 1;
	}

	for (const auto& it : reorganized) {
		cout << it << ' ';
	}
}
