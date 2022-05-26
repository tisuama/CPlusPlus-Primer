#include <iostream>

class Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0;
};


Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

class Sales_data1 {
	friend Sales_data1 add(const Sales_data1&, const Sales_data1&);
	friend std::istream& read(std::istream&, Sales_data1&);
public:
	Sales_data1() = default;
	Sales_data1(const std::string& s, unsigned n, double p): 
		bookNo(s), units_sold(n), revenue(n * n) {}
	Sales_data1(const std::string& s): bookNo(s) {}
	Sales_data1(std::istream&);
	std::string isbn() const { return bookNo; }
	Sales_data1& combine(const Sales_data1&);

private:
	std::string  bookNo;
	unsigned units_sold = 0;	
	double revenue = 0.0;
	mutable size_t access_ctr;
};

constexpr int constexpr_add(int x, int y) {
	return x + y;
}

class Screen {
public:
	Screen& display(std::ostream& os) { do_display(os); return *this; }
	const Screen& display(std::ostream& os) const { do_display(os); return *this; }
	
private:
	void do_display(std::ostream& os) const { os << "haha"; }
	std::string contents;
};

// 有元声明

int main() {
	Sales_data total;
	// total.combine(trans); // 等价于返回total的引用
	// constexpr 
	int x = 1, y = 2;
	constexpr int z = constexpr_add(1, 2);

	// Screen 
	Screen s;	
	s.display(std::cout);
}
