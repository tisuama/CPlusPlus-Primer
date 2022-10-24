## 函数

#### 局部静态对象

局部静态对象在程序执行路径第一次经过对象定义语句时初始化，并且直到程序终止才会被销毁，再次期间函数结束执行也不会对它有影响。
```c++
size_t count_call() {
	static size_t ctr = 0;
	return ++ctr;
}

int main() {
	for (size_t i = 0; i < 10; i++) {
		cout << count_call() << endl;
	}
}
```

#### 使用引用形参返回额外的信息

一个函数只能返回一个值，然后有时函数需要同时返回多个值，引用形参能为我们返回多个结果。

#### const 形参和实参
顶层`const`作用于对象本身
```c++
const int ci = 42;  // 不能改变ci
int i = ci;			// OK，拷贝ci时，顶层const被忽略
int* const p = &i;  // const是顶层
*p = 0;				// OK
```

和其他初始化过程一样，初始化形参时，顶层const会被忽略，换句话说，当形参有顶层const时，传给他的常来那个对象或者非常量对象都是可以的。
```c++
void fcn(const int i); // 传入int 和const int都是可以的
void fcn(int i); 		// ERROR 重复定义函数，由于顶层const被忽略，所以不知道调用哪个函数
```

另一方面，如果形参时某种类型的指针或引用，则通过区分其指向的是常量对象还是非常量对象可以实现函数重载。
```
Record lookup(Account&);
Record lookup(const Account&);

Record lookup(Account*);
Record lookup(const Account*);
```
因为特殊常量引用和常量指针有例外情况，所以对于上面四种情况，由于非常量可以转换成const，所以上面四个函数都能作用于非常量对象或者非常量对象的指针。

#### 指针或者引用形参有const
形参的初始化方式和变量的初始化方式是一样的。

```c++
int i = 42;
const int *cp = &i; // OK
const int &r = i;   // OK
const int &r2 = 32; // OK

int *p = cp; // ERROR， 底层const
int &r3 = r; // ERROR
int &r4 = 32; // ERROR
```
将同样的初始化规则应用于参数传递上可知：
```c++

int i = 0;
const int ci = i;
string::size_type ctr = 0;
reset(&i);  	// OK，调用int*类型的reset函数
reset(&ci);		// ERROR 取地址后变成const int*
reset(i); 		// 调用int&类型的reset函数
reset(42);		// OK
```
#### 数组形参
无法以值得方式使用数组参数，因为数组会被转化成指针。所以当我们传递一个数组时，实际上床底的是指向数组的首元素的指针。
下面三者是等价的：
```c++
void print(const int*)
void print(const int[])
void print(const int[10]) // 维度被忽略
```

#### 数组和可变参数

如果实参数量未知，但是全部实参类型都相同，可以使用`initializer_list`类型的形参

和vector不同的是，initializer_list对象中的元素永远是常量值，我们无法改变initialzer_list对象中元素的值。

#### 省略符形参
省略符形参是为了便于C++程序员访问某些特殊的C代码而设置的，这些代码使用了`vararags`的C标准库功能。

只能出现在形参列表最后一个未知，两种出现形式：
```c++
void foo(param_list, ...); // 逗号可以省略
void foo(...);
```

#### 返回数组指针
由于数组不能被拷贝，但是可以返回数组的指针或引用。
```c++
typedef int arrT[10];
using arrT = int[10];

arrT* func(int i); // 返回一个指向含有10个整数的数组的指针。
```

#### 内联函数和constexpr函数

在大部分机器上，一次函数调用包含一些列工作，调用前要先保存寄存器，并在返回时恢复；可能需要拷贝实参；程序转向一个新的位置继续执行。

内联函数可以避免函数调用开销。通常是将他在每个调用点上“内联地”展开。主要用来优化规模较小，流程直接，频繁调用的函数。

constexpr函数指能用于常量表达式的函数。定义constexpr函数与其他函数类似，不过要遵守几项约定：函数的返回类型及所有形参的类型都得是字面值类型，而且函数体必须有且只有一条return语句。
```c++
constexpr int new_sz() { return 42; }
```
执行该初始化任务时，编译器把对constexpr函数的调用都替换成结果值。为了能在编译过程中展开，constexpr函数被隐式的指定为内联函数。

#### NDEBUG预处理变量

assert行为依赖于一个名为NDEBUG的预处理变量的状态，如果定义了NDEBUG，则assert什么也不做。默认情况下没有定义NDEBUG，因此assert将执行运行时检查。

#### 函数匹配
```c++
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);
```
匹配成功的条件：
1. 该函数每个实参的匹配都不劣于其他可行的函数需要的匹配
2. 至少有一个实参的匹配优于其他可行的函数提供的匹配

f(3, 3.14); // 二义性

#### 函数指针
函数指针指向函数而非对象。
```c++
bool lengthCompare(const std::string&, const std::string&);

// 函数指针
bool (*pf)(const std::string& ,const std::string);
```

我们可以吧函数当成一个值使用，该函数自动转换成指针。
```c++
pf = lengthCompare;
pf = &lengthCompare;
```
此外我们还可以直接使用指向函数的指针调用该函数，而无需解引用。
```c++
bool b1 = pf("hello", "goodbay");
bool b2 = (*pf)("hello'， "goodbay");
bool b3 = lengthCompare("hello", "goodbay");
```

#### 使用auto和decltype用于函数指针

```c++
string::size_type sumLength(const string&, const string&)

decltype(sumLength)* getFunc(const string&);
```

当decltype作用于某个函数时，它返回函数类型而非指针类型。因此我们显示的加上*表示我们需要返回指针，而非函数本身。
