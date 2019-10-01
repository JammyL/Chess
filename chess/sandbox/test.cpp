#include <iostream>

class test {
	int val;
public:
	void set(int i) {val = i;}
	int get() {return val;}
};

class other {
	test val;
public:
	test* get() {return &val;}
};

int main(int argc, char const *argv[])
{
	other* a = new other();
	a->get()->set(5);
	std::cout << "Value is: " << a->get()->get() << "\n";
	return 0;
}
