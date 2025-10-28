#include <stdio.h>
#include <cmath>
#include <string>


#define DEFAULT_BUFFER_LEGTH 256
// Student for Manage student's score of math, physic, chemistry
// the length in the field 'name' is still static(256) the later version will make this field size more dynamic
class Student
{
private:
    char* name = nullptr;
    // the grade is base on base 10 and cannot be negative
    float math_score = 0.f, physic_score = 0.f, chemistry_score = 0.f;

public:
    // input name and score from keyboard
    void input();
    // display student's name & score
    void output() const;
    // Get the Score or  Name
    char* getName(int&) const;
    float getMath() const;
    float getPhysic() const;
    float getChesmistry() const;
    // Set the Score or Name
    void setName(char*);
    void setMath(float);
    void setPhysic(float);
    void setChesmistry(float);
    float calculateGPA() const;
    // convere student's GPA into 4 base (A,B,C,D)
    char grade() const;
};