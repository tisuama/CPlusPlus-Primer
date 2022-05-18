#include <iostream>

struct Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	
	std::string bookNo;
	unsigned units_slod = 0;
	double revenue = 0;
};

class A {
public:
	explicit A(int x): a(x) {}
private:
	int x;
};

class B {
private:
	A a;
};

Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_slod += rhs.units_slod;
	revenue += rhs.revenue;
	return *this;
}

int main() {
	Sales_data total;
	// total.combine(trans); // 等价于返回total的引用
	B b;
}
