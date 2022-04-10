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
	
	const int& ref_1 = a;
	const int& ref_2 = 10;
}
