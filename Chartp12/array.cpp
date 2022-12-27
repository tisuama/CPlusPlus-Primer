#include <iostream>

int main() {
	int* a = new int[10];
	*(a + 2) = 10;
	std::cout << a[2] << std::endl;

	char arr[0];
	char* cp = new char[0];

	std::unique_ptr<int[]> p(new int[10]);
	p[2] = 2;
	std::cout << p[2] << std::endl;
	
}
