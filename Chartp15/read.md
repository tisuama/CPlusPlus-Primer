## Chartp15 面向对象程序设计

#### 继承
通过继承(inheritance)联系在一起的类构成一种层次关系。

在C++语言中，基类将类型相关的函数与派生类不做改变直接继承的函数区分对待。此时基类就将这些函数声明成虚函数(virtual funcion)。

在C++语言中，使用基类的引用（或指针）调用一个虚函数时将发生动态绑定。
```c++
double print_total(ostream& os, const Quote& item, size_t n) {}
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " " << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

// 动态绑定，根据实际传入参数决定调用
print_total(cout, basic, 20);
print_total(cout, bulk, 20);
```

#### 成员函数与继承
C++语言中，基类必须将它两种成员函数区分开来：一种是基类希望其派生类进行覆盖的函数；另一种是基类希望派生类直接继承而不要改变的函数。

>	任何构造函数之外的非静态函数都可以是虚函数。关键字virtual只能出现在类内部的声明语句之前而不能用于类外部的定义。如果一个基类吧一个函数声明为虚函数，则该函数在派生类中隐式的也是虚函数。


#### 定义派生类
派生类经常覆盖它继承的虚函数。如果派生类没有覆盖其基类中的某个虚函数，则该虚函数的行为类似于其他普通的成员，派生类会直接继承其在基类中的版本。

```c++
class Bulk_quote: public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	// override base calss
	double net_price(std::size_t) const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};
```

因为派生类对象含有与其基类对应的组成部分，所以我们能把派生类的对象当成基类对象来使用，而且我们也能将基类的指针或引用绑定到派生类对象中的基类部分上。
```c++
Quote item;
Bulk_quote bulk;
Quote* p = &item;
p = &bulk; 		// p指向bulk的Quote部分
Quote& r = bulk;// r绑定到bulk的Quote部分
```

上列的这种转换通常称为派生类到基类的类型转换（derived-to-base)。

除非我们特别指出，派生类对象的基础类部分会像数据成员一样执行默认初始化，如果想使用其他的基类构造函数，我们需要以类名加圆括号内的实参列表的形式为构造函数提供初始值。

#### 防止继承发生
有时我们不希望其他类继承它，C++11提供了一种防止继承发生的方法，即类名后面跟一个关键字`final`
```c++
class NoDeviced final { };

class Last final: Base { };
```

#### 静态类型与动态类型
当我们使用存在继承关系的类型时，必须将一个变量或其表达式的静态类型（statis type）与该表达式表示对象的动态类型（dynamic type）区分开来。表达式的静态类型在编译时总是已知的。

如果表达式既不是引用也不是指针，则它的动态类型和静态类型一致。

#### 不存在基类向派生类的隐式类型转换

如果基类对象不是派生类对象的一部分，则它只含有基类定义的成员，而不含有派生类定义的成员。
因为一个基类对象可能是派生类对象的一部分，也可能不是，所以不存在基类向派生类的自动类型转换。

```c++
Quote base;
Bulk_quote* bulkP = &base;  // ERROR
Bulk_quote& bulkRef = base; // ERROR
```

除此之外，还有一种情况显得有点特别，即使一个基类指针或者引用绑定在一个派生类对象上，我们也不能执行从基类到派生类的转换。
```c++
Bulk_quote bulk;
Quote* itemP = &bulk; // OK
Bulk_quote* bulkP = itemP; // ERROR
```

>	编译器在编译时无法确认某个特定的转换在运行时是否安全，这是因为编译器只能通过检查指针或者引用的静态类型来推断该转换是否合法。如果在基类中含有一个或多个虚函数，我们可以使用`dynamic_cast`请求一个类型转换，该转换的安全检查将在运行时执行。同样，如果我们已知某个基类向派生类的转换是安全的，则我们可以使用`static_cast`来强制覆盖掉编译器的工作。

#### 在对象之间不存在类型转换
派生类向基类自动类型转换只对指针或者引用有效，在派生类类型和基类类型之间不存在这样的转换。

```c++
Bulk_quote bulk;
Quote item(bulk); 	// 调用基类的Quote::Quote(const Quote&)构造函数
item = bulk; 		// 调用基类的Quote::operator=(const Quote&)拷贝赋值函数
```
