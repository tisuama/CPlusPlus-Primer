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

>	默认情况下，对于一个实例化了的类模板，其成员函数只有在使用时才被实例化。


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
对于任意给定的类型X，都有一个Foo<X>::ctr和一个Foo<X>::count()成员，且所有对象共享。

#### 使用类的类型成员

通过作用域运算符(::)来访问static成员和类型成员（比如类里面的子类类型）。在普通（非模板）代码中，编译器掌握类的定义。他知道通过(::)访问的是是类型还是static成员。

在模板里存在困难，假设T是一个模板类型参数，当编译器遇到类似`T::mem`的代码时，他不知道mem时一个类型成员还是static数据成员，由于模板实例化时才知道，为了处理模板，编译器必须知道名字是否表示一个类型。
```c++
// 比如Foo::mem
// class Foo {
// public:
//		struct mem {};
// };

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
一个类(无论是普通类还是类模板)可以包含本身是模板的成员函数。这种成员函数称为成员模板(`memberj template`)。成员模板不能是虚函数。

#### 普通（非模板）类的成员模板
