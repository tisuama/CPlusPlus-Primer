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
运行时类型识别（run-time type identifycation, RTTI)由两个运算符实现：
1) typeid运算符，用于返回表达式类型
2) dynamic_cast运算符，用于将基类指针或引用安全的转换成派生类的指针或引用(上转)。



