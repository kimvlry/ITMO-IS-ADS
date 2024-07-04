#include <iostream>
#include <regex>

std::string name = R"(([A-Z][a-z]+\s){3})";
std::string age = R"([0-9]{2}\s)";
std::string phone = R"((\+7|7|8)((\([0-9]{3}\)-?)|[0-9]{3})[0-9]{3}-?[0-9]{2}-?[0-9]{2}\s)";
std::string address = R"(g\.[A-Z]{3},\sul\.[A-Z][a-z]+,\sd\.[0-9]+)";

std::regex reg(name + age + phone + address);


int main() {
	int m;
	std::string text;
	std::cin >> m;

	std::getline(std::cin, text);

	for (int i = 0; i < m; ++i) {
		std::getline(std::cin, text);
		std::regex_match(text, reg) ? std::cout << "YES\n" : std::cout << "NO\n";
	}
}
