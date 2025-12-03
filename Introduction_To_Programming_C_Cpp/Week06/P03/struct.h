#ifndef _STRUCT_
#define _STRUCT_

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_CAPACITY 256
#define CURRENT_YEAR 2025
#define DRIVER_AGE 18

struct Date;
struct Name;
struct Student;
struct Course;


struct Date
{
  int day = 1, month = 1, year = 1970;
};



// Name has the base of the rule Naming in Viet Nam, this including 3 part of a Name
// First Name
// Middle Name( can left blank)
// Last Name
struct Name
{
  char first[MAX_NAME_LENGTH];
  char middle[MAX_NAME_LENGTH];
  char last[MAX_NAME_LENGTH];
};





// a Struct of a tipical student in HCMUS
// we will use the ID follow the format of VNU-HCMUS ID
// Student's GPA will be base on base 10 rather than base 4
struct Student
{
  int ID = 0;
  Name name;
  char address[MAX_NAME_LENGTH];
  Date DOB;        // Date of Birth
  float GPA = 0.f; // the base 10 GPA
};




// the Homework will not include the reading from file because reading from file is have not yet learned in the theory course
struct Course {
  bool open = false;
  int capacity = 0;
  int min = 0;
  const int max_size = MAX_CAPACITY;

  char ID[MAX_NAME_LENGTH];
  char name[MAX_NAME_LENGTH];
  Student students[MAX_CAPACITY];
};


#endif