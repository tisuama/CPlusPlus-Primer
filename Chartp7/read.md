## 定义抽象数据类型

```c++
struct Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	
	std::string bookNo;
	unsigned units_slod = 0;
	double revenue = 0;
};
```
成员函数通过一个名为this的额外隐式参数来访问调用它的那个对象。当我们调用一个成员函数时，用请求该函数的对象地址初始化this。
例如：
```c++
total.isbn(); // 等价于Sales_data::isbn(&total);
```
因为this的目的总是指向“这个”对象，所以this是一个常量指针，我们不允许改变this中保存的地址。


#### 引入const成员函数
isbn函数另外一个关键之处是紧随在参数列表之后的const关键字，这里const的作用是修改隐式this指针的类型。

默认情况下，this是指向类类型非常量版版本的常量指针。例如在Sales_data中，this指针的类型是`Sales_data* const`。尽管this是隐式的，但是任然需要遵守初始化规则。不能将this绑定到一个常量对象上。这种情况下，我们不能在一个常量对象上调用普通成员函数。

C++语言的做法是允许吧const关键字放在成员函数的参数列表之后，此时，紧跟在参数列表后面的const表示this是一个指向常量的指针。像这样的const成员函数被称为常量成员函数。

```c++
// isbn函数等价于如下形式：
std::string Sales_data::isbn(const Sales_data* const this) {
	return this->isbn;
}
```

#### 合成默认构造函数

编译器创建的构造函数又称为合成的默认构造函数（synthesized default constructor)。
该构造函数按照如下规则初始化数据成员：
1） 如果存在类内的初始值，则用它来初始化成员
2）	否则，默认初始化

使用情形：只有当类没有声明任何构造函数时，编译器才会自动的生成默认构造函数。
如果类包含有内置类型或者复合类型的成员，只有当这些成员都全被赋予了类内初始化初值时，这个类才适合使用合成的默认构造函数。

#### 拷贝、赋值和析构

一般来说，编译器生成的版本将对对象的每个成员执行拷贝、赋值和销毁操作。

友元：允许其他类或者函数访问它的非公有成员，可以使用友元。
只能出现在类定义的内部，但是出现的位置不限。

#### 类的成员函数初探
在类中，常有一些规模较小的函数适合于被声明称内联函数，定义在类内部的成员函数时自动inline的。


