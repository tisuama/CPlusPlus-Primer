## Chartp18

#### 模板特例化
模板特例化必须定义在原始模板所属命名空间中。和其他命名空间类似，只要我们在命名空间中声明了特例化，就能在命名空间外定义它。

```c++
namespace std {
	template<>
	struct hash<Sales_data>;
}

// 在std空间中声明了模板特例化的声明后，就可以在命名空间std的外部定义它。

template<>
struct std::hash<Sales_data>
{
	// something
};
```
