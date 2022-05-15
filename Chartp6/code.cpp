#include <iostream>
#include <initializer_list>

static int val[10];

size_t count_call() {
	static size_t ctr = 0;
	return ++ctr;
}

void err_msg(const std::initializer_list<std::string>& li) {
	for (auto beg = li.begin(); beg != li.end(); ++beg) {
		std::cout << *beg << std::endl;
	}
	std::cout << "=== err_msg ===" << std::endl;
}

int (*func(int i))[10] {
	
	for (int i = 0; i < 10; i++) {
		val[i] = i;
	}
	std::cout << &val << std::endl;
	return &val;
}

int main() {
	for (size_t i = 0; i < 10; i++) {
		std::cout << count_call() << std::endl;
	}
	
	// const 
	const int i = 25;
	// int* p = &i;	 // ERROR，取地址后变成底层const
	
	// initializer_list	
	err_msg({"haha", "123"});
	
	// 不能拷贝
	int (*ptr)[10] = func(10);
	std::cout << ptr << " " << (*ptr)[5] << std::endl;
}
