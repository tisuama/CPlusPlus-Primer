#include <iostream>

struct D { // 删除器
	D() { std::cout << "D default ctor" << std::endl; }
	D(int x) { std::cout << "D value ctor" << std::endl;}
	D(const D&) { std::cout << "D copy ctor" << std::endl; }
	D& operator=(const D& d) { std::cout << "D copy assing" << std::endl; return *this; }
	D(D&) { std::cout << "D non-copy ctor" << std::endl;}
	D(D&&) { std::cout << "D move ctor" << std::endl; }
	D& operator=(D&& d) { std::cout << "D move assign" << std::endl; return *this; }
};

int main() {
	D d;
	d = D(1);
}
