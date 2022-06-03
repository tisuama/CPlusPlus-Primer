## Chartp12 动态内存与智能指针

### shared_ptr类
智能指针也是模板，使用方式与普通指针类似。解引用一个智能指针返回它指向的对象。
支持操作如下：
```c++
std::shared_ptr<T> sp;

*p; // 解引用p，获得它指向的对象
p.get(); //	返回p中的指针。
swap(p, q); // 交换p、q的指针
p.swap(q); 


// 特有的操作
p = q; // p、q都是shared_ptr，此操作会递减p的引用计数、递增q的引用计数；若p的引用计数变成0，则将其管理的内存释放

p.user_count(); // 返回共享对象的智能指针数量
```
定义和改变shared_ptr的其他用法
```c++
shared_ptr<T> p(q); // q必须为new分配的内存
shared_ptr<T> p(u); // p从unqieu_ptr u那里接管了对象的所有权；将u置空
shared_ptr<T> p(q, d); // p接管了内置指针q所指向对象的所有权。p将使用可调用对象d来代替delete
```

#### 使用动态生存期的资源类
程序使用动态内存出于一下三个原因：
1）程序不知道自己需要使用多少对象
2）程序不知道所需对象的准确类型
3）程序需要在多个对象间共享数据

StrBlob类

#### 直接管理内存
在自由空间分配的内存是无名的，因此new无法为其分配的对象命名，而是返回指向该对象的指针。
```c++
int* pi = new int; // pi指向一个动态分配的、未初始化的无名对象
```
默认情况下，动态分配的对象是默认初始化的，这意味着内置类型或者组合类型的对象的值将是未定义的，而类类型的对象将用默认构造函数进行初始化。

可以使用直接初始化的方式来初始化一个动态分配的对象，可以使用传统的构造方式(使用圆括号)，也可以使用列表初始化{使用花括号}。
```c++
std::string* ps1 = new std::string;
std::string* ps = new std::string();
int* pi1 = new int;   // 默认初始化
int* pi2 = new int(); // 值初始化，pi2为0
```
#### 动态分配的const对象
用new分配const对象是合法的
```c++
const int* pi = new const int(1024);
```
#### 内存耗尽
一旦一个程序用光了所有它可用的内存，new表达式就会失败。默认情况下，如果new不能分配所要求的空间，它会抛出一个bad_alloc的异常。 我们可以改变new的使用方式来阻止它抛出异常。
```c++
int* p1 = new int; // 如果分配失败，抛出bad_alloc异常
int* p2 = new (nothrow) int; // 如果分配失败，返回空指针。
```

#### shared_ptr和new结合使用
如果我们不初始化一个智能指针，它就会被初始化为一个空指针。
```c++
shared_ptr<double> p1;
shared_ptr<int> p2(new int(42));
```

不能将一个内置指针隐式转换成一个智能指针。
```c++
shared<int> clone(int p) {
	return new int(p); // ERROR，不能隐式转换
}


p.reset(q, d); //使用reset来将一个新的指针赋予一个shared_ptr。
p = new int(1024); // ERROR
p.reset(new int(1024)); // OK
```
p.reset(); 若p是唯一指向其对象的shared_ptr，reset会释放此对象。

#### 智能指针与异常
```c++
void f() {
	shared_ptr<int> sp(new int(42));
	// 此段代码抛出一个异常，且在f中未被捕获
    // 使用智能指针可以正确的释放内存
}

函数退出有两种可能，正常处理结束或者发生了异常。无论哪种情况，拒不对象都会被销毁。
```

### unique_ptr
一个`unique_ptr`拥有它所指向的对象。与shared_ptr不同，某个时刻智能有一个unique_ptr指向一个给定对象。当unique_ptr销毁时，它所指向的对象也被销毁。
 
```c++
unique_ptr<double> p1; // OK，可以指向double的unique_ptr
unique_ptr<int> p2(new int(42)); //OK
```
由于unique_ptr拥有它指向的对象，因此unique_ptr不支持普通的$拷贝$或者$赋值$。
```c++
unique_ptr<string> p1(new string("unique_ptr"));
unique_ptr<string> p2(p1); // ERROR，禁止拷贝
unique_ptr<string> p3; 
p3 = p2; // ERROR，禁止赋值
```

unique_ptr支持的操作：
```c++

unique_ptr<T> u1;  // 空的uniqur_ptr
unique_ptr<T, D> u2;

u = nullptr; // 释放u所指向的对象
u.release(); // 放弃对指针的控制权，返回指针，并将u置空
u.reset();   // 释放u指向的对象
u.reset(nullptr); // 如果提供了内置指针去，则令u指向这个对象，否则将u置空
```

#### 传递unique_ptr参数和返回unique_ptr
不能拷贝unqiue_ptr的规则有一个例外，我们可以拷贝或者赋值一个将要被销毁的unique_ptr。
```c++
unqieu_ptr<int> clone(int p) {
	return unqieu_ptr<int>(new int (p)); // OK
}

// 还可以返回局部对象的拷贝
unqieu_ptr<int> clone(int p) {
	unique_ptr<int> ret(new int(p));
	return ret; // OK
}
```

#### weak_ptr
weak_ptr是一种不控制所指对象生存期的智能指针。它指向一个shared_ptr管理的对象，但是不会改变weak_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放，即使有weak_ptr对象。

```c++
weak_ptr<T> w; // 空weak_ptr
weak_ptr<T> w(sp); // 与shared_ptr sp指向相同对象的weak_ptr
w.reset(); // 将w置空
w.lock();  // 如果expired为true，返回一个空shared_ptr，否则返回一个指向w的对象的shared_ptr。
```
由于对象可能不存在，所以我们不能直接使用weak_ptr访问对象，而必须使用lock。
```c++
if (shared_ptr<int> np = wp.lock()) {
	// do something
}
```
