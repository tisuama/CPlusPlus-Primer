#include <iostream>
#include <memory>
#include <vector>

class StrBlob { public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string & t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();

private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string& msg) const ;
};

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string& msg) const {
	if (i >= data->size()) {
		// do something
	}
}

std::string& StrBlob::front() {
	return data->front();
}

std::string& StrBlob::back() {
	return data->back();
}

void StrBlob::pop_back() {
	data->pop_back();
}

struct Foo {
	Foo() { std::cout << "Foo ctor" << std::endl; }
	Foo(const Foo&) { std::cout << "Foo copy ctor " << std::endl; }
	Foo(Foo&&) { std::cout << "Foo move ctor" << std::endl; }
	~Foo() { std::cout << "~Foo dtor" << std::endl; }
};

struct D { // 删除器
	D() { std::cout << "D default ctor" << std::endl; }
	D(const D&) { std::cout << "D copy ctor" << std::endl; }
	D(D&) { std::cout << "D non-copy ctor" << std::endl;}
	D(D&&) { std::cout << "D move ctor" << std::endl; }
	void operator() (Foo* p) const {
		std::cout << "D is deleting Foo" << std::endl;
		delete p;
	}
};

int main() {
	std::shared_ptr<std::string> p1;
	if (p1 && p1->empty()) {
		*p1 = "haha";
	}
	// std::cout << *p1 << std::endl;
	// q = p1;

	std::cout << "=== StrBlob ===" << std::endl;
	
	// StrBlob
	StrBlob b{"1", "2", "3"};
	std::cout << b.size() << std::endl;
	// std::cout << b.front() << std::endl;
	//
	// new
	int* pi = new int(1024);
	std::string* ps = new std::string(10, '9');
	std::vector<int> *pv = new std::vector<int>{0, 1, 2, 3};
	int* pi1 = new int;   // 默认初始化，*pi1的值未定义
	int* pi2 = new int(); // 值初始化为0，*pi2的值为0
	std::cout << *pi1 << " " << *pi2 << std::endl;


	// shared_ptr
	std::unique_ptr<int> p(new int(32));
	// shared_ptr(unique_ptr&& T)
	std::shared_ptr<int> sp(std::move(p));
	assert(p == nullptr);
	std::cout << *sp << std::endl;
	

	// unique_ptr
	std::unique_ptr<std::string> p0(new std::string("haha"));	
	std::unique_ptr<std::string> p2(p0.release());
	std::unique_ptr<std::string> p3(new std::string("test"));
	p2.reset(p3.release());
	assert(p3 == nullptr);
	std::cout << *p2 << std::endl;
	
	D d;
	{
		std::cout << "== test 1 ==" << std::endl;
		std::unique_ptr<Foo, D> up3(new Foo, d);
		// 引用d本身，需要注意作用域
		std::unique_ptr<Foo, D&> up4(new Foo, d);
	}
	{
		std::cout << "== test 2 ==" << std::endl;
		std::unique_ptr<Foo, D> up5(new Foo, D());
	}
	{
		std::cout << "== test 3 ==" << std::endl;
		std::unique_ptr<Foo, D&> up6(new Foo, d);
		std::unique_ptr<Foo, D> up7(std::move(up6));
	}
	
	// 动态数组
	std::shared_ptr<int> p10(new int[10], [](int* p) { delete [] p; });
	p10.reset();
}
