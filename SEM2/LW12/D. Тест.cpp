// #include <blazingio.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>



struct student {
	int isu;
	int points;


	student(int isu, int points)
		: isu(isu)
		, points(points) {
	}
};



std::vector<std::vector<student>> students;

int m, q;


bool by_points(const student& x, const student& y) {
	return x.points < y.points;
}


auto summing_points = [](int sum, const student& s) { return sum + s.points; };


int h(int x) {
	return x % m;
}


int main() {
	std::cin >> m >> q;
	students.resize(m);

	int group, isu, points;
	char option;
	for (int i = 0; i < q; ++i) {
		std::cin >> option;
		if (option == '+') {
			std::cin >> group >> isu >> points;
			group = h(group);
			students[group].emplace_back(isu, points);
		}
		else if (option == '-') {
			std::cin >> group >> isu;
			group = h(group);
			for (auto it = students[group].begin(); it != students[group].end(); ++it) {
				if (it->isu == isu) {
					students[group].erase(it);
					break;
				}
			}
		}
		else {
			std::cin >> group;
			group = h(group);
			if (option == 'a') {
				int sum = std::accumulate(students[group].begin(), students[group].end(), 0, summing_points);
				int average = students[group].empty() ? 0 : sum / students[group].size();
				std::cout << average << '\n';
			}
			else if (option == 'm') {
				if (!students[group].empty()) {
					auto max_student = std::max_element(students[group].begin(), students[group].end(), by_points);
					std::cout << max_student->points << '\n';
				}
			}
		}
	}
}
