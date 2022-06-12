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

class HasPtr {
public:
	HasPtr(const std::string& s = std::string()): ps(new std::string(s)), i(0) {}
	HasPtr(const HasPtr & p): ps(new std::string(*p.ps)), i(p.i) {}
	HasPtr& operator=(const HasPtr&);		
	~HasPtr() { delete ps; }
	
private:
	std::string* ps;
	int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
	delete ps;
	ps = new std::string(*(rhs.ps));
	i = rhs.i;
	return *this;
}


class HasPtr1 {
public:
	HasPtr1(const std::string& s = std::string()):
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	// 拷贝构造也可以使用初始化列表的方式
	HasPtr1(const HasPtr1& p):
		ps(p.ps), i(p.i), use(p.use) { ++*use; }
	HasPtr1& operator=(const HasPtr1&);
	friend void swap(HasPtr1&, HasPtr1&);
	~HasPtr1();
private:
	std::string *ps;
	int i;
	std::size_t* use;
};
HasPtr1::~HasPtr1() {
	if (--*use == 0) {
		delete ps;
		delete use;
	}
}


// 拷贝构造：递增右侧运算符对象的引用计数；递减左侧运算符的引用计数
HasPtr1& HasPtr1::operator=(const HasPtr1& rhs) {
	++*rhs.use;
	if (--*use == 0) {
		delete ps;
		delete use;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}

// 这里并不交换引用计数
inline void swap(HasPtr1& lhs, HasPtr1& rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}

int main() {
	D d;
	d = D(1);
	
	Sales_data s;
	s.set_value(1, 20);
	Sales_data cs(s);
	std::cout << cs.get_value(1) << std::endl;
}
