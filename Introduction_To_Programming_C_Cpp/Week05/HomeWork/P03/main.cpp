#include "lib.h"

// STUDENT'S ID: 24120409
// STUDENT'S NAME: LE THANH PHONG
// CLASS: 25CTT1B/24CTT3


int main() {
  Course courses[2];
  int capacity = 0;
  int choice =  0;
  do {
    menu_list();
    printf("Input choice: ");
    scanf_s("%d",&choice);
    
  } while(list_choice(courses, capacity, choice));

} 