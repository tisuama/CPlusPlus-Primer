#include <iostream>
#include <vector>

class Quote {
public:
	Quote() = default;
	Quote(const std::string& book, double sales_price):
		bookNo(book), price(sales_price) 
	{}

	virtual double net_price(std::size_t n) const {
		return n * 1;
	}

	virtual ~Quote() = default;

private:
	std::string bookNo;	// 书籍isbn编号
protected::
	double price = 0.0;
};

class Bulk_quote: public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	// override base calss
	double net_price(std::size_t) const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

class Disc_quote: public: Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, 
			std::size_t qty, double disc): 
		Quote(book, price),
		quantity(qty),
		discount(disc)
	{}

	double net_price(std::size_t) const = 0;
private:
	std::size_t quantity = 0;
	double discount = 0.0;
};

int main() {
}
