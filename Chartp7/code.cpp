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
};

int Add(int x, int y) {
	return x + y;
}

int main() {
	Sales_data total;
	// total.combine(trans); // 等价于返回total的引用
	int x, y;
	constexpr int z = Add(x, y);
}
