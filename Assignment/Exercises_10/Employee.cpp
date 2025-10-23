#include <stdio.h>
#include <stdlib.h>

#define ID_LENGTH 8
#define BUFFER_SIZE 256
#define MAX_BUFFER_SIZE 8192
// the Basic salary of VietNam on 01/07/2024
#define BASIC_SALARY 2340000
// for each error the Tester found out, he/she will reward this amount of money
#define BONUS_BY_ERROR 200000

template <typename T>
class Array
{
private:
    size_t cur_size, max_capacity;
    int back_idx;                // the idx of the member last in the array
    T *array;

public:
    Array() : max_capacity(MAX_BUFFER_SIZE), cur_size(0), back_idx(-1)
    {
        array = (T *)malloc(cur_size * sizeof(T));
    }
    Array(const size_t n,const T value) : max_capacity(MAX_BUFFER_SIZE), cur_size(n), back_idx(-1)
    {
        array = (T *)malloc(cur_size * sizeof(T));

        // Copy data
        for (int i = 0; i < cur_size; ++i)
            array[i] = value;
    }
    ~Array()
    {
        if (array != nullptr)
        {
            free[] array;
            array = nullptr;
        }
    }

    // operator[] for assign new value directly or obtain the value from it
    T& operator[] (const size_t idx) {
        if (back_idx < idx) {
            printf("Error: Memory access violation, access to memory out of bound\n");
            throw (11);
        }
        return array[idx];
    }

    bool empty() {
        return back_idx == -1;
    }


    void push_back(const T value) {
        // expand the array if there is no cell for data
        if (back_idx == cur_size)
            expand();

        array[++back_idx] =  value;
    }
    void pop_back(const T value) {
        // Only pop data out the array if the array is not empty
        if (!empty()) {
            array[back_idx--] = T();
        }
    }
private:
    // double the size of the array each time the array runs out of cell
    void expand() {
        if (cur_size == max_capacity) {
            printf("Error: Out of memory for allocation\n");
            throw (10);
        }

        size_t old_size = cur_size;
        cur_size *= 2;                  // double the size

        T* temp_arr = array;
        array = (T*) malloc(cur_size * sizeof(T));

        // copy data from  the old  array
        for (int i = 0; i < old_size; ++i)
            array[i] = temp_arr[i];

        free(temp_arr);
    }
};


struct  Date {
    short day = 1, month = 1;
    unsigned int year = 1960;
};

class Employee
{
private:
    Array<char> id, name, address;
    Date birth, BOW;            // BOW: begin of work
protected:
    float payroll;
public:
    Employee() = default;
    ~Employee() = default;

    virtual float salary() = 0;
};


class Manager : public Employee {
private:
    Array<Employee*> employee;
public:
    float salary() override {
        return BASIC_SALARY * payroll;
    }
};
class Programmer : public Employee {
private:
    float overtime;
public:
    // 'value' is the employee's salary for working more time
    Programmer(const float value = 0) {
        if (value < 0) {
            printf("overtime cannot be smaller than 0");
            overtime = 0;
        }
        overtime = value;
    }
    ~Programmer() = default;

    float salary() override {
        return BASIC_SALARY * payroll + overtime;
    }
};
class Designer : public Employee {
private:
    float bonus;
public:
    Designer(const float value = 0) {
        // Bonus must be greater than 0
        if (value < 0) {
            printf("Error: Bouns cannot be smaller than 0\n");
            bonus = 0;
            return;
        }
        bonus = value;
    }
    ~Designer() = default;


    float salary() {
        return BASIC_SALARY * payroll + bonus;
    }
};
class Tester : public Employee {
private:
    unsigned int error;             // number of error that tester found out
public:
    Tester(): error(0) {}
    ~Tester() = default;

    float salary() {
        return BASIC_SALARY * payroll +  BONUS_BY_ERROR * error;
    }
};
int main()
{
}