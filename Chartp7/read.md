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

#### 可变数据成员
可变数据成员（mutable data member)永远不会是const，即使它是const对象的成员。因此一个const长远函数可以改变一个可变成员变量的值。

```c++
class Screen {
public:
	void some_member() const;
private:
	mutable size_t access_ctr;
};

void Screen::some_member() const {
	++access_ctr;
}
```

#### 返回*this的成员函数
```c++
auto display() const {
	return *this; //  返回常量引用
}
```

#### 前向声明
```c++
class Screen
```
不完全类型只能在有限场景下使用：可以定义指向这种类型的指针或引用。

#### 友元再探

除了将普通函数定义称友元，还可以吧其他的类定义成友元，也可以吧其他类的成员函数定义成友元。
当把一个成员函数声明成友元时，必须指出该成员属于哪个类。
``c++
class Screen {
	friend void Window_mgr::clear(ScreenIndex);
};
```

即使在类内部定义友元函数，也必须在类外提供相应的声明从而使得函数可见。
```c++
strcut X {
	friend void f() { /* 可以定义在类内部*/ }
	X() { f(); }
	void g();
	void h();
};

void X::g() { return f(); } // ERROR，友元函数f还未声明
void f(); // 声明该友元函数
void X::h() { return f(); } // OK
```


#### 类的作用域
每个类都会定义自己的作用域。在该类的作用域之外，普通的数据和函数成员只能由对象、引用或者指针使用成员访问运算符来访问。

对于定义在类内部的成员函数来说，首先编译成员的声明，知道类全部可见后才编译函数体。

#### 构造函数初始值列表
有时候可以忽略数据成员函数初始化和赋值之间的差异，但是并非总是这样，如果是const或者引用的话，必须将其初始化。

#### 委托构造函数
C++11扩展了构造函数初始值功能，使得我们可以定义所谓的委托构造函数（delegating constructor)。在委托构造函数内，成员初始值列表只有唯一一个入口，就是类名本身。
```c++
class Sales_data {
public:
	Sales_data(std::string s, unsigned cnt, double price) : bookNo(s), units_slod(cnt), revenue(cnt * private) {}
	Sales_data(): Sales_data("", 0, 0) {}
	Sales_data(std::string): Sales_data(s, 0, 0) {}
};
```

#### 默认构造函数

对于C++新手程序员还说，试图以如下形式声明一个用默认构造函数初始化的对象：
```c++
Sales_data obj(); // ERROR，此处声明了一个函数而非对象
Sales_data obj2; //	OK，obj2是一个对象而非函数
```

#### 隐式类型转换
如果一个构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制。
但是编译器只会自动的执行异步类型转换。
```
item.combine(string("9-999-9999-9")); // OK
// 1. "9-999-9999-9"先转换成std::string
// 2. strgin 转换成Sale_data
item.combine("9-999-9999-9"); 		  // ERROR
```

#### explicit
要求隐式转换的程序上下文中，可以通过将构造函数声明为explicit加以阻止。

explicit支队一个实参的构造函数有效。

发生隐式转换的另外一种情况是执行拷贝形式的初始化，此时只能使用直接初始化为不能使用explicit构造函数。
```c++
Sales_data item1(null_book); // OK，直接初始化
Sales_data item2 = nullptr;  // ERROR，隐式初始化，这里直接调用构造函数，而不是先构造临时变量，在拷贝构造
```

#### constexpr构造函数
尽管构造函数不能是const的，但是字面值常量类的构造函数可以使constexpr函数。
constexpr 构造函数必须初始化所有数据成员，初始值或者使用constexpr构造函数，或者是一条常量表达式。

#### 类的静态成员
static 关键字只能出现在内部的声明语句中。

静态成员函数不予任何对象绑定在一起，也不包含任何this指针。作为结果，静态成员函数不能声明成const。

静态成员变量可以提供const整数类型的类内初始值，不过要求静态成员必须是字面值常量类型的constexpr。

不能在类内部初始化静态成员，相反，必须在类外部定义和初始化每个静态成员。
