#include <iostream>

int main() {
	// const 对象
	const int x = 0;
	std::cout << x << std::endl;
	
	// const 引用
	const int ci = 1024;
	const int& r1 = ci;
	// int& r2 = ci; // 错误，非常量引用绑定一个常量对象	
	const int& xi = 1024; // 这里绑定右值是可以的

	// 引用
	// int& ref = 10;// 引用必须是对象
	int a = 1;
	int& ref = a;
	
	// 底层const
  int i = 0;
 	const int * p2 = &i;	
	const int* const p3 = p2;
	// int *p = p3; // ERROR
	// int &r = ci;	// ERROR
	
	// constexpr
	constexpr int mf = 20;
	constexpr int limit = mf + 1;
	constexpr int* np = nullptr; // const pointer
	
	// typedef 
	typedef char* pstring;
	const pstring cstr = 0;
	const pstring *ps;
	
	// auto
	const int c2 = a, &cr = ci;
	auto b = c2; // int
	auto c = cr; // int
	auto d = &i; // int*
	auto e = &c2; // const int * // 底层const（对const int取地址是底层const)
	const auto f = ci; // const int 顶层const需要手动指定
}
