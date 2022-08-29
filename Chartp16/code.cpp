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

int print(std::initializer_list<int>& il) {
	for (auto x : il) {
		std::cout << "il "  << x << std::endl;
	}
	return 0;
}

template<typename T>
class A {
	public:
		typename T::value_type top(const T& c) {
			return typename T::value_type();
		}
	private:
		T x;
};

// T等于某个类型
template<class T = int>
class Numbers {
public:
	Numbers(T v = 0) : val(v) {}
private:
	T val;
};

int main() {
	// std::cout << compare(1, 2) << std::endl;
	std::cout << compare("haha", "hehe") << std::endl;
	std::cout << compare1(1, 2) << std::endl;
	std::initializer_list<int> L{1, 2, 3};
	print(L);

	Numbers<long double> lots;
	Numbers<> average;

	int v = 1;
	int* p = &v;
	const int* const p1 = p;
	std::cout << *p1 << std::endl;
	
}

