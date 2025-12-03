#include <string.h>
#include <iostream>

int main() {
  char str[20] = "it is what it is";
  char* tmp_str;
  char delim[3] = " ";

  char* result = strtok_s(str, delim, &tmp_str);
  std::cout << result << std::endl;
  result = strtok_s(nullptr, delim, &tmp_str);
  std::cout << result << std::endl;
}