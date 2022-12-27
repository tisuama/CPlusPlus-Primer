#include <iostream>
#include <thread>

template<class T>
class MyUniquePtr {
public:
	explicit MyUniquePtr(): _ptr(nullptr) {}

	explicit MyUniquePtr(T* ptr): _ptr(ptr) {}
	
	~MyUniquePtr() {
		if (_ptr) {
			delete _ptr;
			_ptr = nullptr;
		}
	}

	void operator=(MyUniquePtr&& rhs) {
		_ptr = rhs._ptr;
		rhs._ptr = nullptr;
	}

	void swap(MyUniquePtr& rhs) {
		using std::swap;
		swap(_ptr, rhs._ptr);
	}

private:
	MyUniquePtr(const MyUniquePtr<T>& sp) = delete;
	MyUniquePtr<T>& operator=(const MyUniquePtr<T>& sp) = delete;

	T* 		_ptr;
};

int main() {

}
