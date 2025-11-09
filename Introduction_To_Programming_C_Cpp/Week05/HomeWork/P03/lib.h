#ifndef _LIB_
#define _LIB_

#include "struct.h"


void menu_list();
bool list_choice(Course courses[MAX_CAPACITY], int& capacity, int choice);


// Student Struct -----------------
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

void display_student_information(const Student&);


// Course Struct ------------------------
// Adding Student to the Class
void create_course(Course&);
void update_course_state(Course&);
void check_course_state(Course&);
void add_to_course(Course&, const Student);
// Remove a Student from the Class using ID
void remove_from_course(Course&, const int);


// print a list of all student that is borned in this  month
void filtering_by_month(Course&,const int);
// print a list of all student who is borned in this date
void filtering_by_date(Course&,const Date);
// print a list of all student who has the age above input
void filtering_by_age(Course&,const int);
// print a list of all student who belongs to a specific session
void filtering_by_session(Course&,const int);
// find a Student by ID
void find_by_ID(Course&,const int);
// find a Student by Name
void find_by_name(Course&,const char[MAX_NAME_LENGTH]);
// Sorting by using the input type as the first Criteria
void sort_by_id(Course& course);
void sort_by_firstname(Course& course);
void sort_by_gpa(Course& course);
void sort_by_dob(Course& course);


bool compare_by_id(const Student stu1, const Student stu2);
bool compare_by_gpa(const Student stu1, const Student stu2);
bool compare_by_firstname(const Student stu1, const Student stu2);
bool compare_by_DOB(const Student stu1,const Student stu2);


void display_course(Course& course);
void display_participant(Course& course);



template<typename T>
using operation = bool(*)(T,T);


template<typename T>
void  merge(T array[], const int left, const int mid,  const int right, operation<T> mode) {
  int N = right - left + 1;
  int l = 0, m = mid + 1;
  int i = 0;
  T tmp_arr[N];
  // Sorting
  while (l <= mid && m <= right) {
    tmp_arr[i++] = mode(array[l], array[m]) ? array[l++] : array[m++];
  }
  while (l <= mid) {
    tmp_arr[i++] = array[l++];
  }
  while (m <= right)
  {
    tmp_arr[i++] = array[m++];
  }
  // Copy the sorted data back to the original array
  for (int k = 0; k < N; ++k) {
    array[k + left] = tmp_arr[k];
  }
}
template<typename T>
void merge_sort(T array[], int left, int right, operation<T> type) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    merge_sort(array, left, mid, type);
    merge_sort(array, mid + 1, right, type);

    merge(array, left, mid, right, type);
  }
}


#endif