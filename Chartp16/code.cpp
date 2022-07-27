#include <iostream>
#include <functional>

/*
template<typename T>
int compare(const T &v1, const T& v2) {
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}
*/

template<unsigned N, unsigned M>
int compare(const char(&p1)[N], const char (&p2)[M]) {
	return strcmp(p1, p2);
}

template<typename T>
int compare1(const T& v1, const T& v2) {
	if (std::less<T>{}(v1, v2)) return -1;
	if (std::less<T>{}(v2, v1)) return 1;
	return 0;
}

int main() {
	// std::cout << compare(1, 2) << std::endl;
	std::cout << compare("haha", "hehe") << std::endl;
	std::cout << compare1(1, 2) << std::endl;
}

