#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

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

int date_compare(const Date, const Date);
// Comapre a student base on Student's ID
// Return -1 if st1 < st2, 0 if st1 == st2, 1 if st1 > st2
int compare_student_id(const Student, const Student);
// Compare Students base on GPA first then compare by ID
int compare_student_gpa(const Student, const Student);

int compare_student_name(const Student, const Student);
// Compare Students base on first name then compare by ID
int compare_student_firstname(const Student, const Student);
// Compare student base on the last name then compare by ID
int compare_student_lastname(const Student, const Student);
int compare_student_dob(const Student, const Student);


void get_id(int &id);
void get_full_name(Name &name);
void get_date(Date &date);
void get_address(char addr[MAX_NAME_LENGTH]);
void get_student_information(Student &student);
void get_gpa(float &gpa);


void menu_list()
{
  printf("\n------------ MEUNU --------------\n");
  printf("the choice from 2 --> 6 has the second Cricteria is ID\n");
  printf("1. Compare Student by ID\n");
  printf("2. Compare Student by GPA\n");
  printf("3. Compare Student by Name\n");
  printf("4. Compare Student by First Name\n");
  printf("5. Compare Student by Last Name\n");
  printf("6. Compare Student by DOB\n");
}
bool list_choice(const int choice)
{
  if (choice <= 0 || choice > 6)
  {
    printf("Process to Shutdown the Program\nGoodBye\n");
    return false;
  }

  int res;
  Student st1, st2;
  get_student_information(st1);
  get_student_information(st2);

  switch (choice)
  {
  case 1:
  {
    res = compare_student_id(st1, st2);
    break;
  }
  case 2:
  {
    res = compare_student_gpa(st1, st2);
    break;
  }
  case 3:
  {
    res = compare_student_name(st1, st2);
    break;
  }
  case 4:
  {
    res = compare_student_firstname(st1, st2);
    break;
  }
  case 5:
  {
    res = compare_student_lastname(st1, st2);
    break;
  }
  case 6:
  {
    res = compare_student_dob(st1, st2);
    break;
  }
  }

  printf("\n\n");
  // Print the Result
  if (res == -1)
  {
    printf("Student 1 < Student 2");
  }
  else if (res == 0)
  {
    printf("Student 1 == Student 2");
  }
  else
  {
    printf("Student 1 > Student 2");
  }

  printf("\n\n");

  return true;
}




int main()
{
  int choice;
  do {
    menu_list();

    printf("Input Choice: ");
    scanf_s("%d", &choice);

  } while (list_choice(choice));

  return 0;
}




int date_compare(const Date date1, const Date date2)
{
  if (date1.year < date2.year)
  {
    return -1;
  }
  else if (date1.year > date2.year)
  {
    return 1;
  }
  else
  {
    if (date1.month < date2.month)
    {
      return -1;
    }
    else if (date1.month > date2.month)
    {
      return 1;
    }
    else
    {
      if (date1.day < date2.day)
      {
        return -1;
      }
      else if (date1.day > date2.day)
      {
        return 1;
      }

      else
      {
        return 0;
      }
    }
  }
}

int compare_student_id(const Student st1, const Student st2)
{
  if (st1.ID < st2.ID)
  {
    return -1;
  }
  else if (st1.ID == st2.ID)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
int compare_student_gpa(const Student st1, const Student st2)
{
  if (st1.GPA < st2.GPA)
  {
    return -1;
  }
  else if (st1.GPA > st2.GPA)
  {
    return 1;
  }
  else
  {
    return compare_student_id(st1, st2);
  }
}
int compare_student_name(const Student st1, const Student st2)
{
  int first_comp = strcmp(st1.name.first, st2.name.first);
  int second_comp = strcmp(st1.name.middle, st2.name.middle);
  int thrid_comp = strcmp(st1.name.last, st2.name.last);

  if (first_comp)
  {
    return first_comp;
  }
  else
  {
    if (second_comp)
    {
      return second_comp;
    }
    else
    {
      if (thrid_comp)
      {
        return thrid_comp;
      }
      else
      {
        return compare_student_id(st1, st2);
      }
    }
  }
}
int compare_student_firstname(const Student st1, const Student st2)
{
  int compare = strcmp(st1.name.first, st2.name.first);
  if (compare)
  {
    return compare;
  }
  else
  {
    return compare_student_id(st1, st2);
  }
}
int compare_student_lastname(const Student st1, const Student st2)
{
  int compare = strcmp(st1.name.last, st2.name.last);
  if (compare)
  {
    return compare;
  }
  else
  {
    return compare_student_id(st1, st2);
  }
}
int compare_student_dob(const Student st1, const Student st2)
{
  return date_compare(st1.DOB, st2.DOB);
}



void get_id(int &id)
{
  printf("+ ID: ");
  scanf_s("%d", &id);
}
void get_full_name(Name &name)
{
  printf("+ First Name: ");
  scanf_s(" %[^\n]s\n", name.first);

  printf("+ Middle Name: ");
  scanf_s(" %[^\n]s\n", name.middle);

  printf("+ Last Name: ");
  scanf_s(" %[^\n]s\n", name.last);
}
void get_date(Date &date)
{
  printf("+ get Day, Month, Year: ");
  scanf_s("%d %d %d", &date.day, &date.month, &date.year);
}
void get_address(char addr[MAX_NAME_LENGTH])
{
  printf("+ get Address: ");
  scanf_s(" %[^\n]s\n", addr);
}
void get_gpa(float &gpa)
{
  printf("get GPA: ");
  scanf_s("%f", &gpa);
}
void get_student_information(Student &student)
{
  
  printf("Input Student information:\n");

  get_id(student.ID);
  get_full_name(student.name);
  get_date(student.DOB);
  get_address(student.address);
  get_gpa(student.GPA);
}