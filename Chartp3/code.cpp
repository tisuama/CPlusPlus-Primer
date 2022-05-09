#include <iostream>

using std::cin;
using std::endl;
using std::cout;

int main() {
	// 数组
	unsigned cnt = 42;
	constexpr unsigned sz = 42;	
	int arr[10];
	int *prr[sz];
	// string bad[cnt]; // ERROR	

	int ial[sz] = {0, 1, 2};
	int a2[] = {0, 1, 2};
	// int a5[2] = {0, 1, 2}; // ERROR
 	int *a3 = a2;
	
	// 数组声明
	int *ptrr[10]; // 含有10个整数指针的数组	 
	// int &refs[10]; // ERROR 
	int (*ptr)[10] = &arr; // OK
	int (&ref)[10] = arr; // OK
	
	int *ptr1;
	// ptr1 = 2; // Can not assign a int to int*

	// 数组和指针
	int ia[] = {0, 1, 2, 3, 4, 5};
	auto ia2(ia); // 等价于  auto ia2(&ia[0]);
	// ia2 = 42;
	
	decltype(ia) ia3 = {0, 1, 2, 3, 4, 5};
}
