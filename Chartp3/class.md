## 五花八门初始化

#### 定义一个类变量但是没有初始化时，会使用默认得构造函数进行初始化，所以没有默认构造函数的不能进行默认初始化；定义于任何函数体之外（全局）的类变量先进行零初始化在执行默认初始化，定义于函数体之类的会直接进行默认初始化。

```c++
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

int main() {
	Cat cat1;
	Cat cat2 = Cat(); //显式初始化
	
	Cat1 l_cat;
	std::cout << "global cat age: " << g_cat.age << std::endl;
	std::cout << "local cat age: " << l_cat.age << std::endl;
	
	// 无默认构造函数，无法默认初始化
	// Dog2 dog2; // 编译报错
}
```

#### 如果定义数组时提供了初始值列表，那么未定义的元素先进行零初始化，如果元素是类类型，则再执行默认构造函数。
#### 如果定义数组是为提供初始化列表，则每个元素默认初始化。

#### explicit 禁止的两种隐式类型转换

1. 通过一个实参调用构造函数从构造函数参数类型转向类类型的隐式转换
2. 拷贝构造函数定义用一个对象初始化另一个对象的隐式类型转换
```c++
#include <iostream>
// Cat提供两个构造函数
class Cat {
 public:
    int age;
    // 接收一个参数的构造函数定义了从int型向类类型隐式转换的规则, explicit关键字可以组织这种转换
    Cat(int i) : age(i) {}
    // 拷贝构造函数定义了从一个对象初始化另一个对象的隐式转换
    Cat(const Cat &orig) : age(orig.age) {}
};
int main() {
    Cat cat1 = 10;    // 类型1
    Cat cat2 = cat1;  // 类型2
    std::cout << cat1.age << std::endl;
    std::cout << cat2.age << std::endl;
    return 0;
}
```

