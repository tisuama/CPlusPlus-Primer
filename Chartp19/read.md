## 特殊工具与技术

```c++
std::string* sp = new string("a value");
std::string* arr = new string[10];
```

使用new时实际上执行了：
1) 调用`operator new`(或者`operator new[]`)的标准库函数，分配足够大，原始的，未命名的内存空间
2) 编译运行相应的构造函数以构造这些对象

#### operator new接口和operator delete接口
标准库定义了`operator new`函数和`operator delete`函数的8个重载版本。
```c++
// 这些版本可以抛出bad_alloc异常
void* operator new(size_t); // 分配一个对象
void* operator new[](size_t); // 分配一个数组
void* operator delete(void*) noexcept; // 释放一个对象
void* operator delete[](void*) noexcept; // 释放一个数组
// noexcept指出函数是否抛出异常，如果抛出则调用std::terminate退出进程

// 这些版本承诺不抛出异常
void* operator new(size_t, nothrow_t&) noexcept;
void* operator new[](size_t, nothrow_t&) noexcept;
void* operator delete(void*, nothrow_t&) noexcept;
void* operator delete[](void*, nothrow_t&) noexcept;
```

#### placement new（定位new)
使用placement new的形式构造对象。
```c++
new (place_address) type
new (place_address) type (initializers)
new (place_address) type [size]
new (place_address) type [size]  { initializer list }
```

#### 显式的析构函数调用
```c++
std::string* sp = new std::string("a value");
sp->~string();
```
调用析构函数可以清除给定对象，但是不会释放该对象所在的空间。如果需要，可以重新使用该空间。


### 运行时类型识别。
>	运行时类型识别（run-time type identifycation, RTTI)由两个运算符实现：
1) typeid运算符，用于返回表达式类型
2) dynamic_cast运算符，用于将基类指针或引用安全的转换成派生类的指针或引用(下转)。

当我们将这两个运算符用于某个类型的指针或引用，并且该类型含有虚函数时，运算符将使用指针或引用所绑定对象的动态类型。



#### dynamic_cast

```c++
dynamic_cast<type*>(e);
dynamic_cast<type&>(e); // e左值
dynamic_cast<type&&>(e); // e不能是左值
```
如果dynamic_cast的转换目标是指针类型并且失败了，则结果为0；如果转换目标是引用类型并且失败了，则dynamic_cast运算符抛出一个`bad_cast`异常。



#### typeid
RTTI运算符允许程序向表达式提问：你的对象是什么类型？

#### 嵌套类
一个类可以定义在另一个类的内部，前者称为嵌套类。

嵌套类是一个独立的类，与外层类基本没什么关系。特别的，外层类对象和嵌套类对象是相互独立。在嵌套类的对象中不包含任何外层类定义的成员。类似的，在外层类的对象中不包含任何嵌套类定义的成员。

