#include <iostream>
#include <vector>



class DSU {
	std::vector<int> parents;
	std::vector<int> ranks;

public:
	DSU(int size) {
		parents.assign(size, 0);
		ranks.assign(size, 1);
		for (int i = 0; i < size; ++i) {
			parents[i] = i;
		}
	}


	int Find(int x) {
		if (parents[x] == x) {
			return x;
		}
		return parents[x] = Find(parents[x]);
	}


	void Unite(int x, int y) {
		int x_root = Find(x);
		int y_root = Find(y);
		if (x_root != y_root) {
			if (ranks[x_root] < ranks[y_root]) {
				std::swap(x_root, y_root);
			}
			ranks[x_root] += ranks[y_root];
			parents[y_root] = x_root;
		}
	}


	bool AreConnected(int x, int y) {
		return Find(x) == Find(y);
	}
};



struct querie {
	char command;
	int a;
	int b;
};



int main() {
	int n, m, q;
	int a, b;
	char command;
	std::vector<std::vector<int>> graph;
	std::vector<querie> queries;
	std::vector<std::string> ans;

	std::cin >> n >> m >> q;
	graph.assign(n, {});
	DSU my(n);

	for (int i = 0; i < m; i++) {
		std::cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i < q; i++) {
		std::cin >> command >> a >> b;
		--a;
		--b;
		queries.push_back(querie{command, a, b});

		if (command == '-') {
			graph[a].erase(std::remove(graph[a].begin(), graph[a].end(), b), graph[a].end());
			graph[b].erase(std::remove(graph[b].begin(), graph[b].end(), a), graph[b].end());
		}
	}

	for (int i = 0; i < graph.size(); ++i) {
		for (const auto& neighbour : graph[i]) {
			my.Unite(i, neighbour);
		}
	}

	for (int i = q - 1; i >= 0; --i) {
		if (queries[i].command == '?') {
			bool same = my.Find(queries[i].a) == my.Find(queries[i].b);
			same ? ans.emplace_back("YES") : ans.emplace_back("NO");
		}
		else {
			my.Unite(queries[i].a, queries[i].b);
		}
	}

	std::reverse(ans.begin(), ans.end());
	for (const auto& it : ans) {
		std::cout << it << std::endl;
	}
}
