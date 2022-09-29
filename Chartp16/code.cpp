#include <iostream>
#include <functional>
#include <vector>

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

template<typename T>
auto fcn(T beg, T end)->decltype(*beg) {
	return *beg;
}

template<typename T>
auto fcn1(T beg, T end) -> 
	typename std::remove_reference<decltype(*beg)>::type {
	return *beg;		
}

template<typename T>
void f1(T& x, T& y) {
	x = y;
	std::cout << x << " " << y << std::endl;
}

template<typename T>
void f2(T x, T y) {
	x = y;
	std::cout << x << " " << y << std::endl;
}

template<typename T>
void f3(T&& x) {
	std::cout << x << std::endl;
}

// 可变参数模板
template<typename T>
void printv(std::ostream& os, const T& t) {
	os << t;
}

template<typename T, typename... Args>
void printv(std::ostream& os, const T& t, const Args&... rest) {
	os << t << ",";
 	printv(os, rest...);
}


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
	
	auto sum = std::vector<int>{1, 2, 3};	
	std::cout << fcn(sum.begin(), sum.end()) << std::endl;
	std::cout << fcn1(sum.begin(), sum.end()) << std::endl;
	
	int x = 0;
	// 引用类型时，const属性被保留变成底层const
	const int y = 1;
	f2(y, x);
	
	// int&& rr = x;	// ERROR
	// const int z = 2;
	// f1(y, z);
		
	std::cout << "=== varibale template ===" << std::endl;
	std::string s = "haha";
	printv(std::cout, x, s, 42);	

}

