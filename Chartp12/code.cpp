#include <iostream>
#include <memory>
#include <vector>

class StrBlob {
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string & t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();

private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string& msg) const ;
};

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string& msg) const {
	if (i >= data->size()) {
		// do something
	}
}

std::string& StrBlob::front() {
	return data->front();
}

std::string& StrBlob::back() {
	return data->back();
}

void StrBlob::pop_back() {
	data->pop_back();
}

int main() {
	std::shared_ptr<std::string> p1;
	if (p1 && p1->empty()) {
		*p1 = "haha";
	}
	// std::cout << *p1 << std::endl;
	// q = p1;

	std::cout << "=== StrBlob ===" << std::endl;
	
	// StrBlob
	StrBlob b{"1", "2", "3"};
	std::cout << b.size() << std::endl;
	// std::cout << b.front() << std::endl;
}
