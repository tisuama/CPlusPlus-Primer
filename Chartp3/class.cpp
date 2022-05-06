#include <iostream>

class Cat {
public:
	std::string name;
	Cat() = default;
};

class Cat1 {
public:
	int age;
};	

class Dog1 {
public:
	int age;
	Dog1() {} // 默认构造函数
};

class Dog2 {
public:
	int age;
	Dog2() = delete;		
};

Cat1 g_cat;
Dog1 g_dog;

class Foo {
public:
	Foo(int) {}
private:
	Foo(const Foo&);
};

void func(std::initializer_list<int> l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		std::cout << *it << std::endl;
	}
}

class Cat3 {
public:
	int age;
	Cat3(int i): age(i) { std::cout << "Call Cat3(int) " << std::endl; }
	Cat3(const Cat3& orig): age(orig.age) { std::cout << "Call Cat3(const Cat3& orig)" << std::endl; }
};

class Cat4 {
public:
	int age;
	// Cat4(int i): age(i) { std::cout << "Call Cat4(int) " << std::endl; }
	Cat4() = default;
	explicit Cat4(const Cat4& orig): age(orig.age) { std::cout << "Call Cat4(const Cat4& orig)" << std::endl; }
};

class Cat5 {
public:
	int age;
	explicit Cat5(int i): age(i) {}
	Cat5(const Cat5& orig): age(orig.age) {}
};

int main() {
	Cat cat1;
	Cat cat2 = Cat(); //显式初始化
	
	Cat1 l_cat;
	std::cout << "global cat age: " << g_cat.age << std::endl;
	std::cout << "local cat age: " << l_cat.age << std::endl;
	
	// 无默认构造函数，无法默认初始化
	// Dog2 dog2; // 编译报错
	

	// 数组
	Cat1* my_cat = new Cat1;
	Cat1 cat_array[5] = {*my_cat};
	for (int i = 0; i < 5; i++) {
		std::cout << cat_array[i].age << std::endl;
		// 随机值，0, 0, 0, 0
	}
	
	Foo a1(123);
	Foo a2 = {123}; // C++98 not support 
	Foo a3 {123}; // C++98 not support
	
	// func
	func({1,2,3,4});
	
	// 隐式
	Cat3 cat3 = 10;	 
	
	Cat4 cat4;
	Cat4 cat44(cat4);
	// 隐式调用，ERROR
	// Cat4 cat444 = cat4;
	// std::shared_ptr<int> sp = new int(8); // ERROR
	//
	Cat5 cat5(1);
	Cat5 cat55 = 1;
}

