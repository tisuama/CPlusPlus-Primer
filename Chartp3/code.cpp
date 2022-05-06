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
	return 0;
}
