#include <iostream>
#include <string>
#include <vector>
#include <map>



struct Node {
	int pos;
	char next;


	Node(int p, char n)
		: pos(p)
		, next(n) {
	};
};



std::vector<Node> LZ(std::string s) {
	std::string prefix = "";
	std::map<std::string, int> dict;
	std::vector<Node> ans;

	for (int i = 0; i < s.length(); ++i) {
		if (dict.find(prefix + s[i]) != dict.end()) {
			prefix.push_back(s[i]);
		}
		else {
			ans.emplace_back(dict[prefix], s[i]);
			dict[prefix + s[i]] = dict.size();
			prefix = "";
		}
	}

	if (prefix.length() > 0) {
		ans.emplace_back(dict[prefix], '\0');
	}
	return ans;
}


int main() {
	std::string gutten;
	std::cin >> gutten;

	std::vector<Node> ans = LZ(gutten);
	for (int i = 0; i < ans.size(); ++i) {
		std::cout << ans[i].pos << ' ' << ans[i].next << '\n';
	}
}
