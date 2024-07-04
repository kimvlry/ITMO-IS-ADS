#include <iostream>
#include <vector>
#include <algorithm>



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



struct DSU {
	std::vector<int> presenters;


	void init(int n) {
		presenters.resize(n);
		for (int i = 0; i < n; i++)
			presenters[i] = i;
	}


	int Find(int x) {
		if (presenters[x] == x)
			return x;
		return presenters[x] = Find(presenters[x]);
	}


	void Unite_1(std::vector<edge>& e, std::vector<int>& mst_edges, int ix) {
		int x_root = Find(e[ix].a);
		int y_root = Find(e[ix].b);
		if (x_root != y_root) {
			presenters[x_root] = y_root;
			mst_edges.push_back(ix);
		}
	}


	int Unite_2(std::vector<edge>& e, int ix, int sum, int& edges_counter) {
		int x_root = Find(e[ix].a);
		int y_root = Find(e[ix].b);
		if (x_root != y_root) {
			presenters[x_root] = y_root;
			sum += e[ix].weight;
			++edges_counter;
		}
		return sum;
	}


	bool AreConnected(int x, int y) {
		return Find(x) == Find(y);
	}
};



int MST(DSU& sets, std::vector<int>& mst_edges, std::vector<edge>& edges, int m) {
	std::ranges::sort(edges, comparator);
	int sum = 0;
	for (int i = 0; i < m; i++) {
		edge cur = edges[i];
		if (!sets.AreConnected(cur.a, cur.b)) {
			sets.Unite_1(edges, mst_edges, i);
			sum += cur.weight;
		}
	}
	return sum;
}


int SecondBestMST(DSU& sets, std::vector<int>& mst_edges, std::vector<edge>& edges, int n, int m) {
	int ans = INT_MAX;
	int sum = 0;
	for (const auto mst_edge : mst_edges) {
		sets.init(n);
		int edges_counter = 0;
		for (int i = 0; i < m; i++) {
			if (i == mst_edge)
				continue;
			sum = sets.Unite_2(edges, i, sum, edges_counter);
		}
		if (edges_counter != n - 1) {
			sum = 0;
			continue;
		}
		ans = std::min(ans, sum);
		sum = 0;
	}
	return ans;
}


int main() {
	int n, m;
	std::cin >> n >> m;

	DSU sets;
	sets.init(n);

	std::vector<edge> edges;
	std::vector<int> mst_edges;

	for (int i = 0; i < m; i++) {
		int a, b, w;
		std::cin >> a >> b >> w;
		--a;
		--b;
		edges.emplace_back(a, b, w);
	}

	std::cout << MST(sets, mst_edges, edges, m) << ' ';
	std::cout << SecondBestMST(sets, mst_edges, edges, n, m);
}
