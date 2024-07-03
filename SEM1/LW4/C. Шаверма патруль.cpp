#include <iostream>
#include <vector>



struct Param {
	int value;
	int additional;

	Param(int first, int second) {
		value = first;
		additional = second;
	}
};



void SiftUp(std::vector<Param>& a, int i) {
	while (i != 0 && a[i].value < a[(i - 1) / 2].value) {
		std::swap(a[i], a[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}


void Insert(std::vector<Param>& a, int first, int second) {
	a.emplace_back(first, second);
	SiftUp(a, a.size() - 1);
}


void SiftDown(std::vector<Param>& a, int i) {
	int n = a.size();
	int minimal = i;
	int l_child = 2 * i + 1;
	int r_child = 2 * i + 2;

	if (l_child < n && a[l_child].value < a[minimal].value) {
		minimal = l_child;
	}
	if (r_child < n && a[r_child].value < a[minimal].value) {
		minimal = r_child;
	}
	if (minimal != i) {
		std::swap(a[i], a[minimal]);
		SiftDown(a, minimal);
	}
}


void BuildHeap(std::vector<Param>& a) {
	int n = a.size();
	for (int i = n / 2 - 1; i >= 0; --i) {
		SiftDown(a, i);
	}
}


int ExtractRoot_ByParam(std::vector<Param>& a, bool by_additional) {
	if (!by_additional) {
		int size = a.size();
		int minimal = a[0].value;
		std::swap(a[0], a[size - 1]);
		a.pop_back();
		SiftDown(a, 0);
		return minimal;
	}
	int size = a.size();
	int minimal = a[0].additional;
	std::swap(a[0], a[size - 1]);
	a.pop_back();
	SiftDown(a, 0);
	return minimal;
}


int main() {
	int n, m, start, duration, salary;
	long long ans = 0;
	std::cin >> n >> m;
	std::vector<Param> CurrentBusiness;
	std::vector<Param> Orders;
	for (int i = 0; i < n; ++i) {
		std::cin >> salary;
		CurrentBusiness.emplace_back(salary, 0);
	}
	BuildHeap(CurrentBusiness);

	for (int i = 0; i < m; ++i) {
		std::cin >> start >> duration;
		while (!Orders.empty() && Orders[0].value <= start) {
			Insert(CurrentBusiness, ExtractRoot_ByParam(Orders, true), 0);
		}
		if (!CurrentBusiness.empty()) {
			ans += (long long)duration * (long long)CurrentBusiness[0].value;
			int shwmaster_salary = ExtractRoot_ByParam(CurrentBusiness, false);
			Insert(Orders, start + duration, shwmaster_salary);
		}
	}
	std::cout << ans;
}
