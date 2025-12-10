/*
Dokończyć (niczego nie zmieniając, jedynie dopisując) deklarację klas CContainer, CStack i CLimitedStack tak, żeby poprawnie działały w podanej funkcji main.
*/

#include <vector>

using namespace std;

class EmptyContainer {};

class CContainer
{
protected:
    vector<int> Data;

public:
    virtual bool push(int) = 0;
    virtual int pop() = 0;

    virtual size_t getSizeLimit() = 0;
    virtual ~CContainer() {}
};

class CStack
{
};

class CLimitedStack: public CContainer
{
private:
    static size_t SizeLimit;
public:
	size_t getSizeLimit() override{
		return this->SizeLimit;
	}
	bool push(int a) override{
		if (Data.size()>=SizeLimit) return 0;
		try {
			Data.push_back(a);
			return 1;
		} catch (...) {
			return 0;
		}
	}
	int pop() override{
		try {
			int a = Data.back();
			Data.pop_back();
			return a;
		} catch (...) {
			throw EmptyContainer();
		}
	}
	static void setSizeLimit(const size_t a) {
		SizeLimit = a;
	}
};

