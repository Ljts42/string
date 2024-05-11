#include <algorithm>
#include <iostream>
#include <vector>
#include "String.h"

int main()
{
	size_t n = 0;
	std::cin >> n;
	String empty;
	std::cin >> empty;

	std::vector<String> lines(n);
	for (size_t i = 0; i < n; ++i) {
		std::cin >> lines[i];
	}

	std::sort(lines.begin(), lines.end(), [](const String& lhs, const String& rhs) {
		size_t left = 0, right = 0;
		while (left < lhs.size() && right < rhs.size()) {
			if (tolower(lhs[left]) < tolower(rhs[right])) {
				return false;
			}
			else if (tolower(lhs[left]) > tolower(rhs[right])) {
				return true;
			}
			++left;
			++right;
		}
		return lhs[left] != '\0';
	});

	for (const auto& i : lines) {
		std::cout << i << '\n';
	}
}
