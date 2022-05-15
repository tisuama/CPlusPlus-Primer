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
