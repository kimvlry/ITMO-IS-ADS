#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> graph;


bool Kuhn(int v, graph& g, std::vector<bool>& visited, std::vector<int>& match) {
	if (!visited[v]) {
		visited[v] = true;
		for (auto u : g[v]) {
			if (match[u] == -1 || Kuhn(match[u], g, visited, match)) {
				match[u] = v;
				return true;
			}
		}
	}
	return false;
}


int main() {
	int rows, columns, q;
	int x, y;
	std::cin >> rows >> columns >> q;

	graph g;
	graph free_cells;
	std::vector<bool> visited;
	std::vector<int> match;

	int field_size = rows * columns;
	int candies = 0;

	g.assign(field_size, {});
	visited.assign(field_size, false);
	match.assign(field_size, -1);
	free_cells.assign(rows, std::vector<int>(columns, true));

	for (int i = 0; i < q; ++i) {
		std::cin >> x >> y;
		--x;
		--y;
		free_cells[x][y] = false;
	}

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			if (free_cells[row][col]) {
				int u = row * columns + col;
				int to;

				if (row > 0 && free_cells[row - 1][col]) {
					to = (row - 1) * columns + col;
					g[u].push_back(to);
				}
				if (row < rows - 1 && free_cells[row + 1][col]) {
					to = (row + 1) * columns + col;
					g[u].push_back(to);
				}
				if (col < columns - 1 && free_cells[row][col + 1]) {
					to = row * columns + col + 1;
					g[u].push_back(to);
				}
				if (col > 0 && free_cells[row][col - 1]) {
					to = row * columns + col - 1;
					g[u].push_back(to);
				}
			}
		}
	}

	for (int i = 0; i < field_size; ++i) {
		visited.assign(visited.size(), false);
		Kuhn(i, g, visited, match);
	}

	for (int i = 0; i < field_size; ++i) {
		if (match[i] != -1) {
			++candies;
		}
	}
	candies % 2 == 0 ? std::cout << candies : std::cout << candies + 1;
}
