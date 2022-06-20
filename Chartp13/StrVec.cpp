#include <iostream>
#include <string>
#include <memory>

// StrVec类设计，假话vector版本，只用于string

// elements 指向分配内存的首位置
// first_free 最后一个时机元素之后的位置
// cap 容量 

class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	~StrVec();
	void push_back(const std::string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
	
private:
	std::allocator<std::string> alloc; // 静态分配元素
	void check_n_alloc()  { if (size() == capacity()) reallocate(); }
	std::pair<std::string*, std::string*> alloc_n_copy(
			const std::string*, const std::string*);
	void free();  	   // 销毁元素并释放内存
	void reallocate(); // 获取更多内存并拷贝内存
		
	std::string* elements;
	std::string* first_free;
	std::string* cap;
};

void StrVec::push_back(const std::string& s) {
	check_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e) {
	auto data = alloc.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
	if (elements) {
		// destroy
		for (auto p = first_free; p != elements; )
			alloc.destroy(--p);
		// free
		alloc.deallocate(elements,cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

// 在重新分配内存的过程中移动而不是拷贝元素

StrVec& StrVec::operator=(const StrVec& rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

int main() {
}
