#include <stdio.h>
#include <cstring>


static int count = 0;

class Object
{
private:
    int count_num;
    int data;
public:
    Object();
    Object(const int);
    Object(const Object&);
    ~Object();
};

Object::Object() {
    data=  0;
    count_num = ++count;

    printf("Default Construct Object %d\n", count_num);
}
Object::Object(const int d) {
    data = d;
    count_num = ++count;

    printf("Argument Construct Object %d\n", count_num);
}
Object::Object(const Object& other) {
    data = other.data;
    count_num = ++count;

    printf("Copy Construct Object %d\n", count_num);
}
Object::~Object() {
    printf("Destroy Object %d\n", count_num);
}




void create() {
    Object obj1(5);
    Object obj2;
}



Object objGlobal;
int main() {
    Object obj1;
    create();
    Object obj2(3);
}