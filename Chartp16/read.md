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


