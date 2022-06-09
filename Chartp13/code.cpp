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

class Sales_data {
public:
	Sales_data() = default;
	void set_value(int p, int x) {
		assert(p < 20);
		A[p] = x;
	}
	int get_value(int p) {
		assert(p < 20);
		return A[p];
	}
private:
	std::string bookNo;
	int units_sold = 0;
	double revenue = 0.0;
	int A[20];
};


int main() {
	D d;
	d = D(1);
	
	Sales_data s;
	s.set_value(1, 20);
	Sales_data cs(s);
	std::cout << cs.get_value(1) << std::endl;
}
