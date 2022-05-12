#include <iostream>

int main() {
	std::cout << "====== Test Starting ======" << std::endl;
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
	auto& g = ci;
	auto k = ci, &l = i; // k是整数
	auto &m = ci, *p = &ci; // const int（底层const）
	// auto&n = i, *p2 = &ci; // ERROR	
	const auto& z = ci; 

	// decltype
	const int di = 0, &dj = di;
	decltype(di) xx = 0; // const int 
	decltype(dj) yy = xx;// cnst int&
	// decltype(dj) zz; // ERROR cosnt int &类型必须初始化
	

	std::cout << "====== Test Complete ======" << std::endl;
}
