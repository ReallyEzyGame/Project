#ifndef _LIB_IMPL_
#define _LIB_IMPL_

#include "lib.h"

void menu_list()
{
  printf("\n------------ MEUNU --------------\n");
  printf("1. Create a Course\n");
  printf("2. Output a Course\n");
  printf("3. Add a Student to The Course\n");
  printf("4. Check Minimum\n");
  printf("5. Find all Students borned in Month\n");
  printf("6. Find all Students borned in Date\n");
  printf("7. Find all Students of an Age\n");
  printf("8. Find all Students of a Session\n");
  printf("9. Find all Students have Name\n");
  printf("10. Sort Student by ID\n");
  printf("11. Sort Student by First Name\n");
  printf("12. Sort Student by GPA\n");
  printf("13. Sort Student by DOB\n");
  printf("14. Remove Student from a course\n");
}

bool list_choice(Course courses[MAX_CAPACITY], int &courses_idx, int choice)
{
  if (choice <= 0 || choice > 15)
  {
    printf("Process to Shutdown the Program\nGoodBye\n");
    return false;
  }

  int res;
  Student st1, st2;

  switch (choice)
  {
  case 1:
  {
    printf("Create a New Course\n");
    create_course(courses[courses_idx++]);
    break;
  }
  case 2:
  {
    printf("Choose a course to  Display: ");
    scanf_s("%d", &choice);

    if (0 <= choice && choice < courses_idx)
    {
      display_course(courses[choice]);
      printf("\n");
      display_participant(courses[choice]);
    }
    break;
  }
  case 3:
  {
    printf("Choose a course: ");
    scanf_s("%d", &choice);

    if (0 <= choice && choice < courses_idx)
    {
      Student student;
      get_student_information(student);
      add_to_course(courses[choice], student);
    }
    break;
  }
  case 4:
  {
    printf("Choose a course to Check: ");
    scanf_s("%d", &choice);

    if (0 <= choice && choice < courses_idx)
    {
      update_course_state(courses[choice]);
      display_course(courses[choice]);
      check_course_state(courses[choice]);
    }
    break;
  }
  case 5:
  {
    int month, idx;
    printf("Choose a Course to Filter: ");
    scanf_s("%d", &idx);

    printf("Choose a Month as a Filter: ");
    scanf_s("%d", &month);

    if (0 <= idx && idx < courses_idx && 1 <= month && month <= 12)
    {
      filtering_by_month(courses[idx], month);
    }
    break;
  }
  case 6:
  {
    Date date;
    int idx;

    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    printf("Choice a Date as a Filter: ");
    get_date(date);

    if (0 <= idx && idx < courses_idx)
    {
      filtering_by_date(courses[idx], date);
    }
    break;
  }
  case 7:
  {
    int age, idx;

    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    printf("Choose an Age as a Filter: ");
    scanf_s("%d", &age);

    if (0 <= idx && idx < courses_idx)
    {
      filtering_by_age(courses[idx], age);
    }
    break;
  }
  case 8:
  {
    int session, idx;

    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    printf("Choose a Session as a Filter: ");
    scanf_s("%d", &session);

    if (0 <= idx && idx < courses_idx)
    {
      filtering_by_session(courses[idx], session);
    }
    break;
  }
  case 9:
  {
    int idx;
    char name[MAX_NAME_LENGTH];

    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    printf("Choose a Name: ");
    scanf_s("%s", name);

    if (0 <= idx && idx < courses_idx)
    {
      find_by_name(courses[idx], name);
    }
    break;
  }
  case 10:
  {
    int idx;
    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    if (0 <= idx && idx < courses_idx)
    {
      sort_by_id(courses[idx]);
      display_course(courses[idx]);
      printf("\n");
      display_participant(courses[idx]);
    }
    break;
  }
  case 11:
  {
    int idx;
    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    if (0 <= idx && idx < courses_idx)
    {
      sort_by_firstname(courses[idx]);
      display_course(courses[idx]);
      printf("\n");
      display_participant(courses[idx]);
    }
    break;
  }
  case 12:
  {
    int idx;
    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    if (0 <= idx && idx < courses_idx)
    {
      sort_by_gpa(courses[idx]);
      display_course(courses[idx]);
      printf("\n");
      display_participant(courses[idx]);
    }
    break;
  }
  case 13:
  {
    int idx;
    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    if (0 <= idx && idx < courses_idx)
    {
      sort_by_dob(courses[idx]);
      display_course(courses[idx]);
      printf("\n");
      display_participant(courses[idx]);
    }
    break;
  }
  case 14:
  {
    int idx, id;
    printf("Choose a Course: ");
    scanf_s("%d", &idx);

    printf("Student's ID to remove: ");
    scanf_s("%d", &id);

    if (0 <= idx && idx < courses_idx)
    {
      remove_from_course(courses[idx], id);
      printf("\n");
      display_participant(courses[idx]);
    }
    break;
  }
  }
  printf("\n");
  return true;
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

void display_student_information(const Student &student)
{
  printf("+ ID: %d\n+ Name: %s %s %s\n+ Address: %s", student.ID, student.name.first, student.name.middle, student.name.last , student.address);
  printf("+ Date of Birth: %d/%d/%d\n+ GPA: %.2f", student.DOB.day, student.DOB.month, student.DOB.year, student.GPA);
}

// Course Struct ------------------------
void create_course(Course &course)
{
  char ID[MAX_NAME_LENGTH], name[MAX_NAME_LENGTH];
  int min;

  printf("Course ID: ");
  scanf_s(" %[^\n]s", course.ID);
  printf("Name of Course: ");
  scanf_s(" %[^\n]s", course.name);
  printf("Minimun number to open course: ");
  scanf_s("%d", &course.min);
}
void update_course_state(Course &course)
{
  if (course.min <= course.capacity)
  {
    course.open = true;
  }
  else
  {
    course.open = false;
  }
}
void check_course_state(Course &course)
{
  if (course.open)
  {
    printf("The Course is Open\n");
  }
  else
  {
    printf("The Course is Close\n");
  }
}
void add_to_course(Course &course, const Student student)
{
  if (course.capacity == course.max_size)
  {
    printf("The Course is Full\nThe Student cannot Joined the Course\n");
  }
  else
  {
    course.students[course.capacity++] = student;
  }
}
void remove_from_course(Course &course, const int ID)
{
  bool flag = false; // mark that student has been romoved from the course
  int i = 0;

  for (; i < course.capacity; ++i)
  {
    if (course.students->ID == ID)
    {
      flag = true;
      break;
    }
  }

  // Shift all the data from the right to override the removed data
  if (flag)
  {
    while (i + 1 < course.capacity)
    {
      course.students[i] = course.students[i + 1];
      i++;
    }
    // reduce the number of student paticipate in the course
    course.capacity--;
  }
}

// print a list of all student that is borned in this  month
void filtering_by_month(Course &course, const int month)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    if (course.students->DOB.month == month)
    {
      (course.students[i]);
    }
  }
}
// print a list of all student who is borned in this date
void filtering_by_date(Course &course, const Date date)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    Student stu1 = course.students[i];
    Student stu2;
    stu2.DOB = date;
    if (compare_student_dob(stu1, stu2) == 0)
    {
      display_student_information(course.students[i]);
    }
  }
}
// print a list of all student who has the age above input
void filtering_by_age(Course &course, const int age)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    Student stu = course.students[i];
    if (stu.DOB.year - CURRENT_YEAR >= DRIVER_AGE)
    {
      display_student_information(course.students[i]);
    }
  }
}
// print a list of all student who belongs to a specific session
void filtering_by_session(Course &course, const int session)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    Student stu = course.students[i];
    if (stu.ID / 1000000 == session)
    {
      display_student_information(course.students[i]);
    }
  }
}
// find a Student by ID
void find_by_ID(Course &course, const int ID)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    Student stu = course.students[i];
    if (stu.ID == ID)
    {
      display_student_information(course.students[i]);
    }
  }
}
// find a Student by Name
void find_by_name(Course &course, const char firstname[MAX_NAME_LENGTH])
{
  {
    for (int i = 0; i < course.capacity; ++i)
    {
      Student stu = course.students[i];
      if (strcmp(stu.name.first, firstname) == 0)
      {
        display_student_information(course.students[i]);
      }
    }
  }
}


// Sorting by using the input type as the first Criteria
void sort_by_id(Course &course)
{
  merge_sort(course.students, 0, course.capacity - 1, compare_by_id);
}
void sort_by_firstname(Course &course)
{
  merge_sort(course.students, 0, course.capacity - 1, compare_by_firstname);
}
void sort_by_gpa(Course &course)
{
  merge_sort(course.students, 0, course.capacity - 1, compare_by_gpa);
}
void sort_by_dob(Course &course)
{
  merge_sort(course.students, 0, course.capacity - 1, compare_by_DOB);
}

bool compare_by_id(const Student stu1, const Student stu2)
{
  return stu1.ID < stu2.ID;
}
bool compare_by_gpa(const Student stu1, const Student stu2)
{
  return stu1.GPA < stu2.GPA;
}
bool compare_by_firstname(const Student stu1, const Student stu2)
{
  return strcmp(stu1.name.first, stu2.name.first) == -1;
}
bool compare_by_DOB(const Student stu1, const Student stu2)
{
  return compare_by_DOB(stu1, stu2);
}

void display_course(Course &course)
{
  printf("- ID: %s\n- Course: %s\n", course.ID, course.name);
  printf("- Min: %d\t- Max: %d\t- Current: %d", course.min, course.max_size, course.capacity);
}
void display_participant(Course &course)
{
  for (int i = 0; i < course.capacity; ++i)
  {
    display_student_information(course.students[i]);
  }
}
#endif