#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& sorted) {
	visited[v] = true;
	for (const auto& it : graph[v]) {
		if (!visited[it]) {
			DFS(it, graph, visited, sorted);
		}
	}
	sorted.push(v);
}


void DFS_2(int v, vector<vector<int>>& inverted_graph, vector<bool>& visited, vector<int>& scc, int label) {
	visited[v] = true;
	scc[v] = label;
	for (const auto& it : inverted_graph[v]) {
		if (!visited[it]) {
			DFS_2(it, inverted_graph, visited, scc, label);
		}
	}
}


void Order(vector<bool>& visited, stack<int>& sorted, vector<vector<int>> graph) {
	for (int i = 0; i < graph.size(); ++i) {
		if (!visited[i]) {
			DFS(i, graph, visited, sorted);
		}
	}
}


vector<int> Kosaraju(int n, vector<vector<int>>& graph, vector<vector<int>>& inverted_graph) {
	stack<int> sorted;
	vector<bool> visited;
	visited.assign(n, false);
	Order(visited, sorted, graph);
	visited.assign(n, false);

	vector<int> scc;
	scc.assign(n, -1);
	int label = 0;
	while (!sorted.empty()) {
		int v = sorted.top();
		sorted.pop();
		if (!visited[v]) {
			DFS_2(v, inverted_graph, visited, scc, ++label);
		}
	}
	return scc;
}


int main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> graph;
	vector<vector<int>> inverted_graph;
	graph.assign(n, {});
	inverted_graph.assign(n, {});

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		inverted_graph[b].push_back(a);
	}

	vector<int> scc = Kosaraju(n, graph, inverted_graph);

	for (int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		bool same = scc[a] == scc[b];
		same ? cout << "YES\n" : cout << "NO\n";
	}
}
