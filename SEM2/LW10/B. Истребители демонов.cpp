#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long



struct edge {
	int a;
	int b;
	int weight;


	edge(int a, int b, int w)
		: a(a)
		, b(b)
		, weight(w) {
	}
};



bool comparator(edge& a, edge& b) {
	return a.weight < b.weight;
}



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



ll Kruskal(DSU& sets, std::vector<edge>& edges) {
	ll ans = 0;
	std::sort(edges.begin(), edges.end(), comparator);
	for (int i = 0; i < edges.size(); ++i) {
		edge cur = edges[i];
		if (!sets.AreConnected(cur.a, cur.b)) {
			sets.Unite(cur.a, cur.b);
			ans += cur.weight;
		}
	}
	return ans;
}


int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<edge> edges;
	DSU sets(n);

	int a, b, weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b >> weight;
		--a;
		--b;
		edges.emplace_back(a, b, weight);
	}
	std::cout << Kruskal(sets, edges);
}
