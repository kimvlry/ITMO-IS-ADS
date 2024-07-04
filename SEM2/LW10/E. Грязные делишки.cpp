#include <iostream>
#include <vector>
#include <stack>

#define graph std::vector<std::vector<int>>
using std::vector, std::stack;

int cur_time = 0;
int cur_label = 0;


void LabelComponent(int v, stack<int>& buff, vector<int>& components) {
	++cur_label;
	int last = -1;
	while (!buff.empty() && last != v) {
		components[buff.top()] = cur_label;
		last = buff.top();
		buff.pop();
	}
}


void DFS(int v, int parent, graph& g,
			vector<bool>& visited, stack<int>& buff, vector<int>& components, vector<int>& tin, vector<int>& low) {

	visited[v] = true;
	buff.push(v);
	++cur_time;
	tin[v] = cur_time;
	low[v] = cur_time;

	for (int to : g[v]) {
		if (to != parent) {
			if (visited[to]) {
				low[v] = std::min(tin[to], low[v]);
			}
			else {
				DFS(to, v, g, visited, buff, components, tin, low);
				low[v] = std::min(low[v], low[to]);

				if (tin[v] < low[to]) {
					LabelComponent(to, buff, components);
				}
			}
		}
	}
}


vector<int> FindBiconnected(graph& g, vector<bool>& visited) {
	int n = g.size() + 1;
	stack<int> buff;
	vector<int> components(n);

	vector<int> tin;
	vector<int> low;
	tin.assign(n, -1);
	low.assign(n, -1);

	DFS(0, -1, g, visited, buff, components, tin, low);
	return components;
}


int main() {
	int n, m, q;
	int a, b;

	std::cin >> n >> m >> q;
	++n;

	graph g;
	vector<bool> visited;
	g.assign(n, {});
	visited.assign(n, false);

	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	vector<int> components = FindBiconnected(g, visited);

	for (int i = 0; i < q; ++i) {
		std::cin >> a >> b;
		components[a] == components[b] ? std::cout << "YES\n" : std::cout << "NO\n";
	}
}
