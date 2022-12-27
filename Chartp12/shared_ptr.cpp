#include <iostream>
#include <thread>

template<class T>
class MySharedPtr {
public:
	explicit MySharedPtr()
		: _ptr(nullptr)
		, _ref_count(new int(0))
	{}

	explicit MySharedPtr(T* ptr) 
		: _ptr(ptr)
		, _ref_count(new int(1))
	{}

	~MySharedPtr() {
		Release();
	}

	MySharedPtr(const MySharedPtr& sp) 
		: _ptr(sp._ptr)
		, _ref_count(sp._ref_count)
	{
		AddRefCount();
	}
	
	MySharedPtr& operator=(const MySharedPtr& sp) {
		if (_ptr != sp._ptr) {
			Release();
			_ptr = sp._ptr;
			_ref_count = sp._ref_count;
			AddRefCount();
		}
		return *this;
	}

	T& operator*() {
		return *_ptr;
	}

	T* operator->() {
		return _ptr;
	}
	
	T* Get() {
		return _ptr;
	}
		
	void AddRefCount() {
		++(*_ref_count);
	}


private:
	void Release() {
		if (--(*_ref_count) == 0) {
			delete _ref_count;
			delete _ptr;
		}
	}

	int* 	_ref_count;
	T* 	 	_ptr;
};

class A : public std::enable_shared_from_this<A>{
public:
	~A() {
		std::cout << "~A Destruct" << std::endl;
	}
	std::shared_ptr<A> get_shared() {
		return shared_from_this();
	}
};

int main() {
	std::shared_ptr<A> p0(new A);
	auto p1 = p0->get_shared();
	std::cout <<  p1.use_count() << std::endl;
	auto p2 = p0->get_shared();
	std::cout <<  p2.use_count() << std::endl;
	
	std::weak_ptr<A> w(p0);
	std::cout << w.use_count() << std::endl;
	auto ptr = w.lock();
	std::cout << w.use_count() << std::endl;
}
