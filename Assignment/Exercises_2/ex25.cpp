#include "ex25.h"

void Student::input() {
    char array_c[DEFAULT_BUFFER_LEGTH];
    float num1, num2, num3;

    scanf("Student's name: %s", array_c);
    scanf("Input Math, Physic, Chesmistry Score: %f %f %f", &num1, &num2, &num3);


    // Clamp
    num1 = num1 >= 0.f ? num1 : 0.f;
    num1 = 10.f <= num1 ? 10.f : num1;

    num2 = num2 >= 0.f ? num2 : 0.f;
    num2 = 10.f <= num2 ? 10.f : num2;

    num3 = num3 >= 0.f ? num3 : 0.f;
    num3 = 10.f <= num3 ? 10.f : num3;


    name = array_c;
    math_score = num1;
    physic_score = num2;
    chemistry_score = num3;
}
// display student's name & score
void Student::output() const {
    printf("Student's Name: %s\n", name);
    printf("\t+ Math Score: %.2f\n", math_score);
    printf("\t+ Physic Score: %.2f\n", physic_score);
    printf("\t+ Chemistry Score: %.2f\n", chemistry_score);
}

char* Student::getName(int& size) const {
    size = DEFAULT_BUFFER_LEGTH;
    return name;
}
float Student::getMath() const {
    return math_score;
}
float Student::getPhysic() const {
    return physic_score;
}
float Student::getChesmistry() const {
    return chemistry_score;
}
// Set the Score or Name
void Student::setName(char* new_name) {
    name = new_name;
}
void Student::setMath(float grade) {
    grade = 0 <= grade ? grade : 0;
    grade = grade <= 10.f ? grade : 10.f;

    math_score = grade;
}
void Student::setPhysic(float grade) {
    grade = 0 <= grade ? grade : 0;
    grade = grade <= 10.f ? grade : 10.f;

    physic_score = grade;
}
void Student::setChesmistry(float grade) {
    grade = 0 <= grade ? grade : 0;
    grade = grade <= 10.f ? grade : 10.f;

    chemistry_score = grade;
}
float Student::calculateGPA() const {
    return (math_score + physic_score + chemistry_score) / 3.0f;
}
// convere student's GPA into 4 base (A,B,C,D)
char Student::grade() const {
    float GPA = calculateGPA();

    if (GPA >= 9.0f)
        return 'A';
    if (GPA >= 7.0f)
        return 'B';
    if (GPA >= 5.0f)
        return 'C';
    return 'D';
}