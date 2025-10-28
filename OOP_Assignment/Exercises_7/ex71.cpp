#include <stdio.h>

// Detect  Error: the employee included in a manager must be an employee in the company
// if the employee doesn't exist in the company database ==> cannot add to the employees field of the manager


template <typename T>
class Array;

class Company;
class Employee;
class Engineer;
class Manager;

template <typename T>
class Array
{
private:
    T *data;
    int size, capacity;

public:
    Array() : size(0), capacity(0), data(nullptr) {}
    Array(const int n) : capacity(0)
    {
        if (n <= 0)
        {
            size = 0;
            data = nullptr;
        }
        else
        {
            size = n;
            data = new T[size];

            for (int i = 0; i < size; ++i)
                this->push_back(T());
        }
    }
    // Construct the Array T value from normal array
    // if the size ==> Aaccess memory Violation
    // if the size is smaller than the actual array then the Array will left off all the value behind n
    Array(const int n, const T* arr) : capacity(0) {
        if (n <=  0) {
            size =  0;
            data = nullptr;
        }
        else {
            size = n;
            data = new T[size];

            for (int i = 0; i < size; ++i) 
                *this->push_back(T[i]);
        }
    }
    Array(const Array<T> &arr) : size(arr.size), capacity(arr.capacity)
    {
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = arr.data[i];
    }
    Array(const int n, const T val) : data(nullptr)
    {
        data = new T[n];
        if (!data)
        {
            printf("Error: Memory Allocation Error\n");
            return;
        }

        for (int i = 0; i < n; ++i)
            data[i] = val;
    }
    ~Array()
    {
        if (data)
            delete data;
    }

    int getSize() const
    {
        return size;
    }
    bool empty() const
    {
        return capacity == 0;
    }

    void push_back(const T val)
    {
        // Extend the size of the array
        if (capacity == size)
            if (!extend())
            {
                printf("Error: Out of Memory\nCannot extend the size of the array\n");
                return;
            }
        data[capacity++] = val;
    }
    void pop_back()
    {
        if (capacity)
        {
            data[--capacity] = T();
            return;
        }
    }

    T operator[](const int idx) const
    {
        if (0 <= idx && idx < capacity)
        {
            return data[idx];
        }
        printf("Error: Access Memory Violation\n");
        throw(101);
    }
    T &operator=(const Array<T> &other)
    {
        // if other array has more data than this size then increase the size
        if (this->size < other.capacity)
        {
            this->capacity = other.capacity;
            this->size = other.size;

            delete[] this->data;
            this->data = new T[size];
        }
        // Copy the data
        for (int i = 0; i < capacity; ++i)
            this->data[i] = other.data[i];

        return *this;
    }

private:
    bool extend()
    {
        int tmp_size = size;
        size = size == 0 ? 8 : size * 2;

        T *tmp_arr = data;
        data = new T[size];
        // Memory Allocation Failed
        if (data == tmp_arr)
        {
            return false;
        }
        // Copy the old data
        for (int i = 0; i < tmp_size; ++i)
            data[i] = tmp_arr[i];
        // Release Memory of the old array
        if (tmp_arr)
            delete[] tmp_arr;
        return true;
    }
};



class Company
{
private:
    Array<Employee *> employees;

public:
    Company();
    Company(const Array<Employee*>);
    Company(const Company&);
    

    void addEmployee(Employee*);
    void ereaseEmployee(Employee*);
};

Company::Company() : employees(0) {}
Company::Company(const Array<Employee*> empl_list) : employees(empl_list.getSize()) {
    for (int i = 0; i < employees.getSize(); ++i) {
        Employee* e = employees[i]->clone();

        employees.push_back(e);
    }
}
Company::Company(const Company& other) : employees(other.employees.getSize()) {
    for (int i = 0; i < employees.getSize(); ++i) {
        Employee* e = employees[i]->clone();

        employees.push_back(e);
    }
} 


void Company::addEmployee(Employee* e) {
    if (e) {
        employees.push_back(e);
    }
}
void Company::ereaseEmployee(Employee*) {}


class Employee
{
private:
    Array<char> ID, name;
protected:
    float base, bonus_rate;
public:
    Employee() = default;
    Employee(const Array<char>, const Array<char>);
    virtual ~Employee() = default;

    
    void setID(const Array<char>);
    void setName(const Array<char>);

    Array<char> getID();
    Array<char> getName();


    virtual Array<char> getRole() = 0;
    virtual Array<char> describeWork() = 0;
    virtual Employee* clone() = 0;
    virtual int calculateSalary() = 0;
};





void Employee::setID(const Array<char> new_id) {

}
class Engineer : public Employee
{
private:
    float over_work_time; // Unit: hour
public:
    Engineer();
    // Initialize time the Engineer over work & the bonus rate for that over work time
    Engineer(const float, const float);
    Engineer(const Engineer &);
    ~Engineer() = default;


    Array<char> getRole() final;
    Array<char> describeWork() final;
    int calculateSalary() final;
    Engineer* clone() final;
};


Engineer::Engineer() : Employee() {}
Engineer::Engineer(const float over_time, const float bonus) : Employee(), over_work_time(over_time) {}
Engineer::Engineer(const Engineer &other) : Employee(), over_work_time(other.over_work_time) {}
Engineer::~Engineer() = default;


Array<char> Engineer::getRole()
{
    return Array<char>(9, "Engineer");
}
Array<char> Engineer::describeWork() {
    char arr_ch[256];

    printf("Input Describsion: ");
    scanf("%s", arr_ch);

    return Array<char>(256, arr_ch);
}
Engineer* Engineer::clone() {
    Engineer* e = new Engineer(*this);
    return this;
}
int Engineer::calculateSalary()
{
    return base + over_work_time * bonus_rate;
}




class Manager : public Employee
{
private:
    Array<Employee *> employees;

public:
    Manager();
    Manager(Array<Employee *> &);
    Manager(const Manager &);
    ~Manager() = default;

    Array<char> getRole() final;
    Array<char> describeWork() final;
    Manager* clone() final;
    int calculateSalary() final;
};

Manager::Manager() : Employee(), employees(0) {}
Manager::Manager(Array<Employee*>& empl_list) : Employee() {
    employees = Array<Employee*>((int)empl_list.getSize());

    for (int i = 0; i < employees.getSize(); ++i) {
        Employee* e(empl_list[i]->clone());

        employees.push_back(e);
    }
}
Manager::Manager(const Manager& other) : Employee(), employees(other.employees.getSize()) {
    for (int i = 0; i < employees.getSize(); ++i) {
        Employee* e = other.employees[i]->clone();

        employees.push_back(e);
    }
}
Manager::~Manager() {
    for (int i = 0; i < employees.getSize(); ++i)
        delete employees[i];
}


Array<char> Manager::getRole() {
    return Array<char>(16, "Manager");
}
Array<char> Manager::describeWork() {
    char arr_ch[256];
    printf("Input Descripton: ");
    scanf("%s", arr_ch);

    return Array<char>(256,arr_ch);
}
Manager* Manager::clone() {
    Manager* manager = new Manager(*this);
    return manager;
}
int Manager::calculateSalary() {
    return base + bonus_rate * employees.getSize();
}

