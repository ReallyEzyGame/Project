#include <iostream>
#include <vector>


class Base {
public:
    virtual void Print(std::ostream& os) = 0;
    friend std::ostream& operator<<( std::ostream& os, Base& base) {
        base.Print(os);
        return os;
    }
};


class Derived1 : public Base {
private:
    int _of01;
public:
    Derived1(const int& v) {
        _of01  = v;
    }

    void Print(std::ostream& os) override {
        os << "D1 - " << _of01;
    }
};

class Derived2 : public Base {
private:
    int _of02;
public:
    Derived2(const int& v) {
        _of02 = v;
    }

    void Print(std::ostream& os) override {
        os << "D 2- " << _of02;
    }
};



int main() {
    std::vector<Base*> ds;

    ds.push_back(new Derived1(13));
    ds.push_back(new Derived1(17));
    ds.push_back(new Derived2(24));
    ds.push_back(new Derived2(28));

    for (int i = 0; i < ds.size(); ++i) {
        std::cout << *ds[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    system("pause");
    return 0;
}