#include "lib.h"




int main() {
    Person person1("Le Thanh Phong", Date{7,5,2006});
    Person person2("Donald E. Knuth", Date{10,1,1938});

    Company company("My Company");

    company.addEmpl(person1, 2);
    company.addEmpl(person2, 1);

    std::cout << company << std::endl;
    std::cout << "Total Salary: " << company.totalSalary() << std::endl;
}