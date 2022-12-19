## Chartp2 基础
#### 2.3 复合类型
1. 引用并非对象，相反的，它只是为一个已经存在的对象起另外一个名字。
```c++ 
int &ref = 10; // ERROR
```
2. 指针和引用不同的点：1）指针本省就是一个对象，允许指针赋值与拷贝，而且在生命周期内他可以先后指向不同的对象 2）指针无需在定义时赋初值

3. 空指针（null pointer） 不指向任何对象，nullptr是一种特殊的字面值，他可以被转换成任意其他的指针类型。 `NULL`是一个预处理变量，它的值为0

>	`void*`指针是一种特殊的指针，可以存放任意对象的地址；不能直接操作`void*`指针所指对象，因为我们不知道这个对象到底是什么类型。

> 指向指针的指针，通过`*`的个数可以区分指针的级别，也就是`**`表示指针的指针。

> 指向指针的引用。引用本身不是一个对象，不能定义引用的指针，但是可以存在指针的引用。PS：要理解r类型到底是什么，简单的办法是从右向左阅读r的定义，离变量名最近的符号对变量的类型有最直接的影响。
```c++
int i = 42;
int *p;
int *&r = p;
```


#### 2.4 const 限定符
1. const 对象一旦创建后其值就不会改变，所以const对象必须初始化

2. 默认情况下const对象仅在文件内有效。当以编译时初始化的方式定义一个const对象时，编译器会在编译过程中把用到该变量的地方替换成对应的值。为了执行上诉替换，编译器必须知道变量的初始值。

3. const引用，称为对常量的引用，表示不能修改它所绑定的对象。
```c++
const int ci = 1024;
const int& r1 = ci; // OK
r1 = 42; // ERROR
int& r2 = ci; //ERROR 试图让一个非常量引用指向一个常量对象。

```

4. pointer to const: 指向常量的指针
	 const pinter: 常量指针

```c++
const double pi = 3.14;
double *ptr = &pi; // ERROR
const double *cptr = &pt; //OK
double dval = 3.14;
cptr = &dval; // OK
```
5. 顶层const 
一般用顶层const表示对象本身是一个常量，而用底层const表示指针所指对象是一个常量。
更一般的，顶层const表示任意对象是常量，包括算术类型、类、指针等类型，底层const则与指针和引用等复合类型的基本类型部分有关。
```c++
int *const p1 = &i;  // 顶层const
const int* p2 = &c1; // 底层const
const int& r = ci;   // 底层const
```
底层const限制：当执行对象拷入如拷出操作时，拷入和拷出对象必须具有相同的底层const资格。

6. constexpr：指值不会改变，且在编译过程中就能计算得到结果的表达式。
一个对象是否为常量表达式由它的数据类型和初始值共同决定。
```c++
const int max_files = 20; // 常量表达式
const int limit = max_files + 1; // 常量表达式
const int sz = get_size(); // 非常量表达式
```
在一个复杂系统中，很难分辨是不是常量表达式，C++11允许将变量声明为constexpr来让编译器验证是否为常量表达式。声明为constexpr的变量一定是一个常量，且只能用常量表达式初始化。

constexpr修饰指针时限定符仅仅对指针有效，而对指针指向的类型无效。
```c++
const int* p = nullptr; // p是一个指向常量类型的指针
constexpr int* q = nullptr; // q是一个指向整数的常量指针
```

7. 指针、常量和类型的别名
遇到使用了类型别名的声明语句时，人们往往会尝试替换成原来的样子，这种做法是错误的。
```c++
typedef char* pstring;
const pstring cstr = 0; // 不要理解成等价于const char* cstr
const pstring *ps;
```

#### auto类型说明符
C++11引入auto类型说明符，让编译器通过初始值来推算变量类型，显然，auto定义的变量必须有初始值。

auto也能在一条语句中声明多个变量，但是初始的基本数据类型必须一致。首先就是使用引用对象作为初始值时，参与对象初始化的起始时引用对象的值。此时编译器以引用对象类型作为auto的类型。

其次，auto一般会忽略掉顶层const，而保留底层const;
```c++
const int ci = i, &cr = ci;
auto b = ci; // b 是一个整数
auto c = cr; // c是一个整数，此时cr是ci的别名，ci本身是一个顶层const
auto d = &i; // d 是一个整形指针
auto e = &ci // e是一个指向整数常量的指针
```
设置一个const引用时，初始值中的顶层常量属性仍然保留，
```c++
auto& g = ci; // g是一个整形常量引用，绑定到ci;
auto& h = 42; // ERROR，不能为非常量引用绑定字面值。
const auto& j = 42; // OK
```
此时初始值中顶层常量属性仍然保留。

#### decltype类型指示符
使用情况：有时候希望从表达式类型推断出要定义的变量类型，但是不想用该表达式的值初始化变化。

decltype 处理顶层const和引用的方式与auto有些许不同。如果decltype使用的表达式是一个变量，则decltype返回该变量的类型（包括顶层const与引用在内）。

decltype与引用：如果decltype使用的表达式不是一个变量，则decltype返回表达式结果对应的类型。
```c++
int i = 32, *p = &i, &r = i;
decltype(r + 0)  b;// r + 0 结果为int
decltype(*p) c; // ERROR , *p返回int&，必须初始化
```
decltype如果使用的是一个不加括号的变量，则得到的结果就是该变量的类型；如果给变量加上了一层或者多层括号，编译器就会把它当做成一个表达式。
```c++
// decltype 的表达式如果是加上了括号的变量，结果将是引用
decltype((i)) d; // ERROR, d是int&，必须初始化
```

#### 预处理器
工作在`编译期`之前，典型功能是头文件替换。
