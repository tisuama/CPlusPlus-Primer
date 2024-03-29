## 模板与泛型编程

面向对象编程（OOP）和泛型编程都能处理在编写程序时不知道类型的情况。不同之处在于：OOP能处理类型在程序运行之前都未知的情况；而在泛型编程中，在编译时就能获知类型。

#### 函数模板

函数模板（function template)是一个公式，可以用来生成特定类型的函数版本。
```c++
template<typename T>
int compare(const T &v1, const T& v2) {
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}

std::cout << compare(1, 0) << std::endl;
```
当我们调用函数模板时，编译器通常用函数实参来为我们推断模板实参。

编译器用推断出的模板参数来为我们实例化一个特殊版本的函数，这些由编译器生成的版本通常称为实例。

模板参数：通常使用`class`和`typename`关键字。

### 非类型模板参数
除了定义类型参数，还可以在模板中定义非类型参数。一个非类型参数表示一个值而非一个类型。不需要通过关键字`class`或`typename`来指定非类型参数。当一个模板实例化时，非类型参数被用户提供的或者编译器推断出的值所替代，这些值必须是常量表达式。
```c++
typename<unsigned N, unsigned M>
int compare(const char(&p1)[N], const char (&p2)[M]) {
	return strcmp(p1, p2);
}
```
在模板定义内，模板非类型参数是一个常量值。在需要常量表达式的地方，可以使用非类型参数。例如：数组的大小

#### inline和constexpr的函数模板
函数模板可以声明为inline或constexpr的，如同非模板函数一样。
```c++
template<typename T>
intline T min(const T&, const T&);
```

#### 模板编译
当编译器遇到一个模板定义时，它并不生成代码。只有当我们实例化出模板的一个特定版本时，编译器才会生成代码。当我们使用模板时（而不是定义），编译器才生成代码，这一特性影响我们如果阻止代码以及错误何时被检测到。

>	通常我们调用一个函数时，编译器只需要掌握函数的声明。类似的，当我们使用一个类类型的对象时，类定义必须是可用的，但成员函数的定义不必已经出现。因此，我们将类定义（可以没有成员函数定义）和函数声明放在头文件中，而普通函数和类成员函数定义放在源文件中。

模板则不同：为了生成一个实例化版本，编译器需要掌握函数模板或者类模板函数的定义。因此，与非模板代码不同，模板的头文件通常即包括声明也包括定义。

#### 模板错误
编译器会在三个阶段报告模板相关的错误：
第一个阶段：模板本身，通常只是语法错误。
第二个阶段：编译器遇到模板调用时。在此阶段，编译器任然没有很多的检查。对于函数模板调用，编译器通常检查实参数目是否正确，它还能检查参数类型是否匹配。对于类模板，编译器可以检查用户是否提供了正确数目的模板实参。
第三个阶段：模板实例化时，只有这个阶段才能发现类型相关的错误。依赖于编译器如何管理实例化，这类错误可能在链接时才报告。

>	保证传递给模板的实参支持模板所有要求，以及这些操作在模板中能正确的工作，是调用者的责任。

## 类模板
类模板（class template）是用来生成类的蓝图。与函数模板不同之处是，编译器不能为类模板推断模板参数类型。 类模板不是一个类型名。类模板用来实例化类型，而一个实例化的类型总是包含模板参数的。

#### 类模板与成员函数
与往常一样，当我们在类外定义一个成员时，必须说明成员属于哪个类。

```c++
template<typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);	
	}
};
```

#### 类模板成员的实例化
默认情况下，一个类模板的成员只有当程序使用到它时才进行实例化。

```c++
Blob<int> blobs = {0, 1, 2, 3, 4};
for (size_t i = 0; i != blobs.size(); i++) {
	blobs[i] = i * i;
}
```
这里Blob类只实例化了它和三个成员函数`operator[]`, `size`和接受`initializer_list<int>`的构造函数

>	默认情况下，对于一个`实例化了`的类模板，其成员函数只有在使用时才被实例化。


#### 在类代码内简化模板类名的使用

当我们使用一个类模板类型时必须提供模板实参，但这一规则有一个例外。在类模板自己的作用域中，我们可以直接使用模板名儿不提供实参。

```c++
template<typename T>
class BlobPtr {
public:
	BlobPtr(): curr(0) {}
	// 注意这里是Blob
	BlobPtr(Blob<T> &a, size_t sz = 0):
		wptr(a.data), curr(sz) { }
	
 	// 前置递增和递减，这里BlobPtr等价于BlobPtr<T>
	BlobPtr& operator++();
	BlobPtr& operator--();
};
```
当我们在类模板外定义其成员时，必须记住，我们并不在类的作用域中，知道遇到类名才表示进入类的作用域。

#### 模板类型的别名
类模板的一个实例定义了一个类类型，与任何其他类一样，我们可以定义typedef来引用实例化的类。
```c++
typedef Blob<string> StrBlob;
```

由于模板不是一个类型，我们不能定义typedef 引用一个模板。即：无法定义一个typedef引用Blob<T>

#### 类模板的static成员
```c++
template<typename T>
class Foo{
public:
	static std::size_t count() { return ctr;}
private:
	static std::size_t ctr;
};
```

与其他任何static数据成员相同，模板类的每个static数据成员必须有且只有一个定义。但是，类模板的每个实例都有一个独有的static对象。因此，与定义模板的成员函数类似，我们将static成员也定义称模板。
对于任意给定的类型X，都有一个Foo<X>::ctr和一个Foo<X>::count()成员，且所有对象共享。

#### 使用类的类型成员

通过作用域运算符(::)来访问static成员和类型成员（比如类里面的子类类型）。在普通（非模板）代码中，编译器掌握类的定义。他知道通过(::)访问的是是类型还是static成员。

在模板里存在困难，假设T是一个模板类型参数，当编译器遇到类似`T::mem`的代码时，他不知道mem时一个类型成员还是static数据成员，由于模板实例化时才知道，为了处理模板，编译器必须知道名字是否表示一个类型。
```c++
// 比如Foo::mem
class Foo {
public:
 	struct mem {};
};

template <typename T>
typename T::value_type top(const T& c) {
	if (!c.empty()) {
		return c.back();
	} else {
		return typename T::value_type(); // 这里调用构造函数，值初始化？
	}
}
```
#### 模板默认实参
就像我们能为函数参数提供默认实参一样，我们也可以提供默认实参`(default  template argument)`.C++11我们可以为函数和类模板提供默认实参，而更早的C++标准只允许为类模板提供默认实参。
```c++
template <typename T, typename F = less<T>>
int compare(const T& v1, const T& v2, F f = F()) {
	if (f(v1, v2)) return -1;
	if (f(v2, v1)) return 1;
	return 0;
}
```
#### 模板默认实参与类模板
无论任何时候使用一个类模板，都需要在模板名之后接上尖括号。尖括号指出类必须从一个模板实例化而来。特别，如果一个类模板为所有模板参数都提供了了默认实参，而且我们希望使用默认参数，则必须在模板名之后跟一个尖括号对。
```c++
// 这里T = int，直接等于类型
template<class T = int>
class Numbers {
public:
	Numbers(T v = 0) : val(v) {}
private:
	T val;
};

Numbers<long double> lots;
Numbers<> average;
```

#### 模板声明
模板声明必须包含模板参数。
```c++
// 声明但是不定义compare
template<typename T>
int compare(const T&, const T&);
template<typename T>
class Blob;
```
模板的声明通常在一起放置在文件的开始位置，出现于任何使用这些模板的代码之前。


### 成员模板
一个类(无论是普通类还是类模板)可以包含本身是模板的成员函数。这种成员函数称为成员模板(`member template`)。成员模板不能是虚函数。

#### 普通（非模板）类的成员模板

类似`unque_ptr`所使用的默认删除器类型类型，如果我们希望删除器适用于任何类型，可以将运算符定义称一个模板。

```c++
// 函数对象类，定义类指针执行delete
class DebugDelete {
public:
	DebugDelete(std::ostream& s = std::cerr): os(s) { }
	template<typename T>
	void operator() (T* p) const {
		os << "deleteing unique_ptr" << std::endl;
		delete p;
	}

private:
	std::ostream &os;
};

// 可以将DebugDelete用作unique_ptr的删除器。
std::unique_ptr<int, DebugDelete> p(new int, DebugDelete());
std::unique_ptr<string, DebugDelete> p(new string, DebugDelete());
```

#### 类模板的成员模板
对于类模板成员，我们也可以为其定义一个成员模板，在此情况下，类和成员各自有自己的、独立的参数。
```c++
template<typename T>
class Blob {
public:
	template<typename It>
	Blob(It b, It e);
};
```
与类模板的普通成员数据不同，成员模板是函数模板。当我们在类外定义一个成员模板时，必须同时为类模板和成员模板提供模板参数列表。

```c++
template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e): data(std::make_shared<std:vector<T>>(b, e))
{}
```

#### 控制实例化
模板被使用时才会进行实例化，这一特性意味着，相同的实例可能出现在多个对象文件中。我两个或多个独立便利的源文件使用相同的模板，并且提供相同的模板参数时，每个文件就会有该模板的一个实例。
在大系统中，多个文件中实例化相同的模板额外开销可能非常严重。在新标准中，可以通过显式实例化来避免这种开销。
```c++
extern template declaration; // 实例化声明
template declaration;	 // 实例化定义
```

当编译器遇到extern模板声明时，他不会在本文件中生成实例化代码。使用extern表示承诺程序在其他位置有该实例化的一个非extern声明（定义）。

由于编译器在使用一个模板时自动对其进行实例化，因此extern声明必须出现在任何使用此实例化版本之前。

```c++
extern template class Blob<string>; // 实例化声明
extern template int compare(const int&, const int&);

Blob<string> sa1,sa2;
// Blob<int> 及其接受initializer_list的构造函数在本文件中实例化
Blob<int> a1 = {0, 1, 2, 3, 4, 5,};
Blob<int> a2(a1); // 拷贝构造函数在本文件中实例化。
int i = compare(a1[0], a2[0]); // 实例化出现在其他位置。

实例化文件必须为每个在其他文件中声明为extern的类型和函数提供一个非extern的定义
template 
int compare(const int&, const int&)

template
class Blob<string> // 实例化类模板的所有成员;
```

当编译器遇到一个实例化定义时，他为其生成代码。

一个类模板实例化$定义$会实例化该模板的所有成员，包括内联成员函数。当编译器遇到一个实例化定义时，他不了解程序使用哪些成员函数。因此，与处理类模板的普通实例化不同，编译器会实例化该类的所有成员。即使我们不使用某些成员，它也会被实例化。


#### 类型转换与模板类型参数
从函数实参确认模板实参的过程被称为模板实参推断(`template argument deduction`)
只有有限的几种类型转换会自动的适用于这些实参。编译器通常不会对实参进行类型转换，而是生成新的模板实例。

与往常一样，顶层const无论是在形参中还是实参中都会被忽略。
在其他类型转换中，能在调用中应用于函数模板的包括如下两项：
1. const转化，可以将一个非const对象的引用或指针传递给一个const的引用或指针形参。
	
2. 如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换成指向其首元素的指针。类似的，一个函数实参可以转换成该函数类型的指针。
其他任意类型的转换，如算术转化，派生类向基类转换，以及用户定义的转换，都不适用于函数模板

```c++
template<typename T>
T fobj(T, T);

template<typename T>
T fref(const T&, const T&);

std::string s1("value");
const std::string s2("another value");
fobj(s1, s2); // 调用fobj(string, string); const 被忽略
fref(s1, s2); // 调用fref(const string&, const string&); 

int a[10], b[20];
fobj(a, b); // 调用fobj(int*, int*); 忽略了数据维度
fref(a, b); // ERROR, a[10], b[20]不同的类型，数组维度不可忽略
```

#### 函数模板显式实参
在某些情况下，编译器无法推断出模板实参的类型，在另外一些情况下，我们希望允许用户控制模板实例化。
```c++
template<typename T1, typename T2, typename T3>
T1 sum(T2 x, T3 y) {
	return x + y;
}

auto v3 = sum<long long>(i, lng); // T1通过用户指定，T2, T3编译器推断
// =>  long long sum(int, long);
```

正常类型转换可以应用于：
a) 显式指定的实参（如上面的例子）
b) 普通函数实参（不涉及模板参数的部分) 
```c++
template<typename T>
ostream& print(ostream& os, const T& obj);  // os可以正常转换
```

#### 尾置返回类型与转换
当我们希望用户确定返回类型时，用显式模板实参表示函数模板返回值类型时有效的，但是其他情况下，要求显式指定模板实参
会给用户添加额外负担，且可能不会带来什么好处。
比如我们希望编写一个函数，接受表示序列的一对迭代器并返回序列中一个元素的引用。
```c++
template<typename T>
??? &fcn(T beg, T end) {
	return *beg;
}

在编译器遇到函数列表之前，beg都是不存在的，这时候需要使用尾置返回类型，它可以使用函数参数。
template<typename T>
auto fcn(T beg, T end) -> decltype(*beg) {
	return *beg;
}
// decltype(*beg)推断出元素的引用作为函数返回值
```

#### 类型转换的标准库模板
下面返回数据值得拷贝
```c++
template<typename T>
auto fcn2(T beg, T end) ->
	typename remove_reference<decltype(*beg)>::type {
	return *beg;
}
// typename的作用是告诉编译器，type是一个类型
```
这里标准类型转换规则：
>	remove_reference<T>  
-	若T为X&或X&&，则remove_reference<T>::type为X
-	否则, remove_reference<T>::type为T

#### 函数指针和实参推断

当我们使用一个函数模板初始化一个函数指针或者一个为一个函数指针赋值，编译器使用指针的类型来推断模板实参。
```c++
template<typename T>
int compare(const T&, const T&);

int (*pf1)(const int&, const int&) = compare;
// pf1中参数类型决定了T模板实参的类型
```

#### 模板实参推断和引用
为了理解如何从函数调用进行类型推断，考虑下面的例子:
```c++
template<typename T>
void f(T& p);
// 其中p是一个模板类型参数T的引用。
```
>	非常重要的是记住两点：编译器会应用正常的引用绑定规则；const是底层的，不是顶层的。

##### 从左值引用函数参数推断类型
当一个函数参数是模板类型参数的一个普通（左值）引用时，绑定规则告诉我们，只能传递一个左值（如一个变量或者一个返回引用类型的表达式）。实参可以使const类型，也可以不是。
```c++
template<typename T>
void f1(T&);

f1(i); // OK, i是int，T被推断为int
f1(ci);// OK, i是const int，T被推断为const int
f1(5); // ERROR, 传递的参数不是左值
```
#### 引用折叠
```c++
template<typename T> 
void f3(T&&) // 可以传递右值
f3(32); //OK
```
通常不能将一个右值引用绑定到左值身上，但是C++在正常的绑定规则外有两个例外。
1. 第一个例外影响右值引用参数的推断如何进行。当我们将一个左值（如i）传递给函数的右值引用参数，且此右值引用参数指向模板类型的参数（如T&&）时，编译器推断模板类型参数为实参的左值引用类型。因此调用f3(i)是，编译器推断T为int&，而非int。

2. T被推断为int&看起来意味着f3的函数参数应该是一个类型int&的右值引用。通常我们不能定义引用的引用。但是，通过类型别名或者模板类型参数间接定义时可以的。
这种情况下，引入第二个列外：如果我们间接创建一个引用的引用，则这些引用形成了引用`折叠`。在所有情况下（除了一个例外），引用会折叠成一个普通的左值引用类型。


只有一个特殊的情况引用会折叠成右值引用：右值引用的右值引用。即对于给定类型X：

- X& &， X& &&, X&& &都折叠成X&
- 类型X&& &&折叠成X&&

f3(i)的实例化结果可能为: void f3<int&>(int& &&) => void f3<int&>(int&)

>	这两条规则导致一个重要的结果：
	如果一个函数参数是一个指向模板类型参数的右值引用，则他可以被绑定到一个左值；且
	如果一个实参是一个左值，则推断出模板实参类型将是一个左值引用，且函数参数将被实例化为一个普通的左值引用函数。

这两个规则暗示，我们可以将任意类型的实参传递给T&&类型的函数参数。对于这种类型的参数，显然既可以传递右值，又可以传递左值。

*实际情况中，右值引用通常用于两种情况：模板转发其实参或模板被重载。*
```c++
template<typename T>
void f(T&&); 	  // 绑定到非const右值

template<typename T> 
void f(const T&); // 绑定到左值和const右值
```
### 理解std::move
标准库`move`函数是使用右值引用模板的一个很好的例子。我们不能直接将一个右值引用绑定到一个左值上，但是可以用move获得一个绑定到左值的右值引用。由于move本质上可以接受任意类型的实参，因此我们不会惊讶于它是一个函数模板。

```c++
// std::move实现
template<typename T>
typename remove_reference<T>::type&& move(T&& t) {
	return static_cast<typename remove_reference<T>::type&&>(t);
}
```

首先move的函数参数`T&&`是一个指向模板类型参数的右值引用。通过引用折叠，此参数可以与任何类型匹配。特别是，我们既可以传递给move一个左值，也可以传递给它一个右值。
```c++
std::string s1("hi"), s2;
s2 = std::move(std::string("byte")); // 推断为move(std::string && t) => move(std::string&& t);
s2 = std::move(s1);	// 推断为move(std::string& && t) => move(std::string& t);
```
#### 不使用move，从左值static_cast到一个右值也是允许的
虽然不能隐式的将一个左值转换为右值引用，但是可以使用static_cast显式的将一个左值转换为右值引用。

对于操作右值引用的代码来说，将一个右值引用绑定到一个左值允许他们截断左值。

> A = B：A绑定到B，B赋值给A


### 转发std::forward
某些函数需要将其一个或多个实参连同类型不变的转发给其他函数。这种情况下，我们需要保持被转发实参所有性质，包括实参类型是否是const以及实参是左值还是右值。

```c++
// flip是一个不完整的实现：顶层const和引用丢失
template<typename F, typename T1, typename T2>
void flip(F f, T1 t1, T2 t2) {
	f(t2, t1); // 注意这里倒转了t2、t1
}

void f(int v1, int& v2) {
	std::cout << v1 << " " << ++v2 << std::endl;
} 

int i = 1, j = 1;
f(42, i); // i的值变成2
flip(f, j, 42); // f不会改变j，因为flip => void flip(void(*fn)(int, int&), int t1, int t2);
```

#### 定义能保持类型的函数参数
通过将一个函数定义为一个指向模板类型参数的右值引用，我们可以保持其对应是实参的所有类型。而底层引用参数（无论是左值还是右值）使得我们保持其对应的const属性，因为在引用中，const是底层的.
```c++
template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
	f(t2, t1);
}
```
想想调用flip(f, j, 42)发生了什么？将传递给t1一个左值j。所以当递增v2时，j的值也发生改变。

这个版本的flip解决了一半问题。它对于接受一个左值引用的函数工作的很好，但不能用于接受右值引用参数的函数。例如:
```c++
void g(int&& i, int& j) {
	std::cout << i << " " << j << std::endl;
}
```
当我们试图通过flip调用g时，则参数t2将被传递给g的右值引用参数。即使我们传递一个右值给flip，传递给g的将是flip的t2参数。
函数参数与其他任何变量一样，都是左值表达式，因此，flip中对g的调用将传递给g右值引用参数一个左值。
```
flip(g, i, 42); // ERROR，不能从左值实例化int&&
```

### 在调用中使用std::forward保持类型信息

我们可以使用一个名为std::forward的新标准库设施来传递flip参数，它能保持原始实参类型。std::forward必须通过显式模板实参来调用。forward返回该显式实参类型的右值引用。即std::forward<T>返回类型是T&&。

通常情况下，我们使用forward传递那些定义为模板类型参数的右值引用的函数参数。通过返回类型上的引用折叠，forward可以保持给定实参的左值/右值属性。
```c++
template<typename T> intermediary(T && arg) {
	finalFcn(std::forward<T>(arg);
}
```

使用forward重写翻转函数:
```c++
template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}
```
### 模板重载
函数模板可以被另一个模板或者普通非模板函数重载，与往常一样，名字相同的函数必须具有不同数量或类型的参数。
函数匹配规则：
-	如果同样好的函数只有一个是非模板函数，则选择此函数
-	如果同样好的函数中没有非模板函数，而有多个匹配的函数模板，选择更特例化的模板。
-	否则此调用有歧义。


### 可变参数模板

一个可变参数模板就是一个接受可数目参数的模板函数或者模板类。
`class...`或者`typename...`指出接下来参数表述零个或多个类型的列表；一个类型后面跟一个省略号表示零个或多个给定类型的非类型参数列表。

存在两种参数包：模板参数包，表示零个或多个模板参数；函数参数包，表示零个或多个函数参数。

如果一个参数的类型是模板参数包，则此参数也是一个函数参数包。
```c++
template<typename T, typename... Args> // 模板参数包
void foo(const T& t, const Args& ...rest); // 函数参数包

int i = 0; double d = 3.14; string s = "hello";
foo(i, d, ,42, s); => void foo(const int&, const double&, const int&, const string&);
foo(s, 42, "hi");  => void foo(const string&, const int&, const char[3]&);
foo("hi"); // 空包 => void foo(const char[3]&);
```

>	sizeof...运算符： 当我们需要知道包中有多少元素时，可以使用sizeof...运算符。sizeof...返回一个常量表达式，而且不会对其实参求值。
```c++
template<typename... Args> 
void g(Args... args) {
	std::cout << sizeof...(Args) << std::endl; // 类型参数数目
	std::cout << sizeof...(args) << std::endl; // 函数参数数目
}
```
### 包扩展

对于一个参数包，除了获取其大小外，我们唯一能做的事情就是扩展(expand)。扩展一个包就是将它分解为构成的元素，对于每个元素应用模式，获得拓展后的列表。我们通过模式右边放一个省略号(`...`)
来触发扩展操作。
```c++
template<typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args&... rest) { // 第一次包扩展
	os << t << ", ";
	return print(os, rest...); // 第二次包扩展
}
```
第一次包扩展操作扩展模板参数包，扩展Args，编译器将模式(`const Args&`)应用到模板参数包Args中的每个元素。因此，此模式扩展结果是一个逗号分割的零个或多个类型的列表，每个类型都形如`const type&`。例如：
```c++
print(cout, i, s, 42);
	||
	\/
第一次扩展: print(ostream&, const int&, const std::string&, const int&);
第二次扩展: print(os, s, 42);
```

第二个扩展发生在对print的调用中，在此情况下，模式是函数参数包的名字（即reset)。此模式扩展出一个由包中元素组成的，逗号分割的列表。

### 转发参数包
保持类型信息是一个两阶段的过程。首先，为了保持实参中的类型信息，必须将empace_back的函数参数定义为模板类型参数的右值引用。
```c++
calss StrVec {
public:
	template<class... Args>
	void emplace_back(Args&&...) {
		chk_n_alloc();
		alloc.construct(first_free++, std::forward<Args>(args)...);
	}
};
// 模板参数包扩展中的模式是&&，意味着每个函数参数将是一个指向其对应实参的右值引用。
```

其次，当emplace_back将这些实参传递给construct时，我们必须使用forward来保持其实参的原始类型。


### 模板特例化

```c++
// 第一种:
template<typename T> 
int compare(const T&, const T&); // 可以比较任意两个类型

// 第二种:
template<size_t N, size_t M>
int compare(const char(&)[N], const char(&)[M])；  // 处理字符串常量

const char* p1 = "hi", *p2 = "mon";
compare(p1, p2); // 第一个版本
compare("hi", "mom"); // 第二个版本
```
只有当我们传递给compare一个字符串字面常量或者一个数组时，编译器才会调用接受两个非类型模板参数的版本。如果我们传递给它字符指针，就会调用第一个版本。

为了处理字符指针，我们可以为第一个版本的compare定义个模板特例化(template sperialization)版本。一个特例化版本就是模板的一个独立的定义，在其中一个或多个模板参数被指定为特定的类型。


#### 定义函数模板特例化
使用关键字`template`后跟一个空尖括号来表示我们为原模板所有参数提供实参。
```c++
template<>
int compare(const char* const& p1, const chara* const &p2) {
	return strcmp(p1, p2);	
}
```
理解此特例化最困难的之处是函数参数类型。当我们定义一个特例化版本时，函数参数类型必须与一个先前声明的模板中对应的类型匹配。
我们定义此函数一个特例化版本，其中T为`const char*`。我们的函数要求一个指向此类型const版本的引用。因此特例化版本中使用的类型是`const char* const &`: 一个指向const char的const 指针的引用。


#### 函数重载与模板特例化
当我们定义函数模板特例化版本时，本质上接管了编译器的工作，即我们为原模板的一个特殊实例提供了定义。一个特例化版本本质上是一个实例，而非函数名的一个重载版本。

### 类模板特例化
除了特例化函数模板，我们还可以特例化类模板。作为例子，我们将为标准库hash模板定义一个特例化版本。

一个特例化的hash类必须定义：
1. 一个重载的调用运算符，他接受一个容器关键字类型的对象，返回一个size_t
2. 两个类型成员，`result_type`和`argument_type`，分别为运算符的返回类型和参数类型
3. 默认构造函数和拷贝赋值运算符


值得注意的是，我们的hash函数计算所有三个数据成员的哈希值，从而与我们为`Sale_data`定义的`operator==`是兼容的。默认情况下，为了处理特定的关键字类型，无需容器会组合使用`key_type`
对应的特例化hash版本和`key_type`上的相等运算符。
```c++
// 使用hash<Sale_data>和Sale_data的operator==
unordered_set<Sale_data> data;
```

### 类模板部分特例化
与函数模板不同，类模板特例化不必为所有模板参数提供实参。我们可以指定一部分而非所有模板参数。

```c++
template<class T>
struct remove_reference {
	typedef T type;
};

// 部分特例化版本
template<class T>
struct remove_reference<T&> { // 左值引用
	typedef T type;
};


template<class T>
struct remove_reference<T&&> { // 右值引用
	typedef T type;
};
```
由于一个部分特例化的版本本质上是一个模板，与往常一样，我们首先定义模板参数。

#### 特例化成员而不是类

我们可以只特例化成员函数而不是特例化整个模板。
```c++
template<typename T>
struct Foo {
	Foo(const T& t = T()): mem(t) {}
	void Bar() { }
	T mem;
};

template<>	// 我们正在特例化一个模板
void Foo<int>::Bar() { // 我们正在特化Foo<int>成员的Bar
}


Foo<string> fs; // 实例化Foo<string>::Foo();
fs.Bar(); // 实例化Foo<string>::Bar();
Foo<int> fi; // 实例化Foo<int>::Foo();
fi.Bar(); // 使用特例化版本的Foo<int>::Bar();
```
