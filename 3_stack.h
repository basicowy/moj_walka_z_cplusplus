/*
Dokończyć (niczego nie zmieniając, jedynie dopisując) deklarację klas CElement i CStack tak, żeby poprawnie działały w podanej funkcji main.
*/



class EmptyStack {};

class CElement
{
private:
    int value;
    friend class CStack;
public:
    CElement() : value(0) {}           // konstruktor domyślny
    CElement(int v) : value(v) {}
};

class CStack
{
private:
    CElement* pData;
    unsigned int top;
    unsigned int size;

public:
    CStack() : pData(nullptr), top(0), size(0) {};
    CStack(const CStack& p) {
        if (p.size == 0) {
            size = 0;
            top = 0;
            pData = nullptr;
            return;
        }
        CElement* new_pdata = new CElement[p.size];
        for (unsigned int i =0 ; i < p.size; i++) {
            *(new_pdata + i) = *(p.pData + i);
        }
        pData = new_pdata;
        top = p.top;
        size = p.size;

    }
    ~CStack() {
        delete[] pData;
    }
    void push(int a);
    int pop();
    CStack& operator=(const CStack& p) {
        CElement* new_pdata = new CElement[p.size];
        for (unsigned int i =0 ; i < p.size; i++) {
            *(new_pdata + i) = *(p.pData + i);
        }
        delete[] pData;
        pData = new_pdata;
        top = p.top;
        size = p.size;
        return *this;
    }
    friend ostream& operator<<(ostream& s,const CStack& p) {
        for (int i = (int)p.top ; i >= 0; i--) {
            s << (p.pData + i)->value<< ' ' ;
        }
        return s;
    }

};
void CStack::push(int a) {
    CElement* new_pdata = new CElement[size+1];
    if (size != 0) {
        for (unsigned int i =0 ; i < size; i++) {
            *(new_pdata + i) = *(pData + i);
        }
        delete[] pData;

    }
    (new_pdata+size)->value = a;
    pData = new_pdata;
    if (size != 0) top++;
    size++;
}
int CStack::pop() {
    if (size == 0) {
        throw EmptyStack();
    }
    CElement* new_pdata = new CElement[size-1];
    for (unsigned int i =0 ; i < size-1; i++) {
        *(new_pdata + i) = *(pData + i);
    }
    int val = (pData + top)->value;
    delete[] pData;
    pData = new_pdata;
    if (top != 0)top--;
    size--;
    return val;
}