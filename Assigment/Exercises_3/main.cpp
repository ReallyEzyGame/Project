#include <stdio.h>

class Cnt {
private:
    static int cnt;
public:
    Cnt() {cnt++;}
    ~Cnt() {cnt--;}
    static void count() {
        printf("%d\n", cnt);
    }
};

int Cnt::cnt = 1;



int main() {
    Cnt c1, c2;

    c1.count();

    Cnt::count();

}