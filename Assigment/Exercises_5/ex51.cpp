#include <string>

#include <stdio.h>


class Address;
class Student;
class ExchangeStudent;



class Address{
private:
    std::string street, city, state;
public:
    void display() {
        printf("Address:\n\t+ Street: %s\n\t+ City: %s\n\t+ State: %s\n",street.c_str(),city.c_str(), state.c_str());
    }
};


class Student {
public:
    std::string name;   // ASCII, example: Le Thanh Phong
    size_t ID;          // using HCMUS's ID rules
    float GPA;          // using base 10, Evaluate by char: Excellent: 'A', Great : 'B', Good : 'C', Pass : 'D', Fail : 'F' base on HCMUS's rules to evaluate grade for student
    Address addr;
public:
    Student() = default;


    char getGrade() {
        if (GPA >= 9.0f) return 'A';
        if (GPA >= 8.0f) return 'B';
        if (GPA >= 6.5f) return 'C';
        if (GPA >= 5.0f) return 'D';

        return 'F';
    }
    void display() {
        printf("----- Student Information -----\n");
        printf("\t+ ID: %llu\n\t+ Name: %s\n\t+ GPA: %.2f", ID, name.c_str(), GPA);

        printf("\n\t");
        addr.display();
    }  
};


class ExchangeStudent : public Student {
private:
    std::string home_country;
    int duration;           // using month as unit
public:
    ExchangeStudent(const std::string home_ctry,const int dur) : Student(), home_country(home_ctry) {
        if (dur < 0) duration = 0;      // Clamp to avoid False case
        else duration = dur;
    }
    ExchangeStudent(Student student, std::string home_ctry, const int dur) : Student(student), home_country(home_ctry) {
        if (dur < 0) duration = 0;      // Clamp to avoid False case
        else duration = dur;
    }
    void updateDuration(int month) {
        if (month >= 0) {
            duration = month;
        }
    }
    void display() {
        Student::display();
        printf("\t+ Home Country: %s\n\t+ Duration: %d\n", home_country.c_str(), duration);
    }
};