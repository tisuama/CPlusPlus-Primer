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
protected:
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

class Disc_quote: public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, 
			std::size_t qty, double disc): 
		Quote(book, price),
		quantity(qty),
		discount(disc)
	{}

	double net_price(std::size_t) const;
private:
	std::size_t quantity = 0;
	double discount = 0.0;
};

struct Base {
	int memfcn() {
		std::cout << "Base::memfcn" << std::endl;
	}
}; 
struct Derived: Base {
	int memfcn(int) {
		std::cout << "Derived::memfcn" << std::endl;
	}
};

class Base1 {
public:
	virtual int fcn() { 
		std::cout << "Base fcn" << std::endl;
	}
};
class D1: public Base1 {
public:
	int fcn(int) {std::cout << "D1 fcn(int)" << std::endl; } 	// 形参列表与Base中的fcn不一致，仅仅是同名隐藏，但是并没有覆盖
	virtual void f2() { std::cout << "D1 f2()" << std::endl; }
};

class D2 : public D1 {
public:
	int fcn(int) { std::cout << "D2 fcn(int)" << std::endl; } // 非虚函数，隐藏了D1::fcn(int)
	int fcn() { std::cout << "D2 fcn()" << std::endl; }	// 覆盖了Base的虚函数fcn
	void f2() { std::cout << "D2 f2()" << std::endl; }	// 覆盖了D1的f2
};
int main() {
	// 非动态绑定时
	Derived d; Base b;
	b.memfcn(); 	// OK
	d.memfcn(10); 	// OK
	// d.memfcn();		// ERROR，memfcn被隐藏。一旦memfcn名字找到，编译器就不在继续查找。
	d.Base::memfcn(); 	// OK
					
	Base* bb = &d;
	bb->memfcn();


	// Base 动态绑定时
	Base1 bobj; D1 d1obj; D2 d2obj;
	Base1* bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
	bp1->fcn();
	bp2->fcn();
	bp3->fcn();

	D1* d1p = &d1obj; D2* d2p = &d2obj;
	// bp2->f2(); // ERROR
	d1p->f2(); // D1::f2();
	d2p->f2(); // D2::f2();
}
