#include "array.h"
#include "person.h"


// This part had not yet develop
// -------------------------------------
// Detect  Error: the employee included in a manager must be an employee in the company
// if the employee doesn't exist in the company database ==> cannot add to the employees field of the manager
// -------------------------------------
// This Programm will not allow user to copy list of  employee from 1 company to other since the program is still lack of Smart Pointer class to manages Pointer better
// This lead to an Fatal error: when copy Pointer type from one Array to another, it will cause the destruct( delete) from one array first, the other array access to such pointer will cause Access Memory Violation

class Company
{
public:
    class Employee : public Person
    {
    private:
        static int _current_id;

    private:
        int _id;

    protected:
        int _salary;
        float _bonus;

    public:
        // We only allow a Person who has Identity to Becomes an Employee
        Employee(const Person &person);
        ~Employee();

        int id() const;
        int bonus() const;
        int baseSalary() const;
        void updateBonus(const float value);
        void updateBaseSalary(const int value);

        virtual int salary() const = 0;
        virtual String job() const = 0;
        virtual String describe() const = 0;
    };

    class Engineer : public Employee
    {
    private:
        int _over_time;

    public:
        Engineer(const Person &person);
        Engineer(const Employee &empl);
        Engineer(const Person &person, const int time);
        Engineer(const Employee &empl, const int time);
        ~Engineer();

        int overTime() const;
        void updateOverTime(const int time);

        int salary() const final;
        String job() const final;
        String describe() const final;
    };

    class Manager : public Employee
    {
    private:
        Array<int> employees;
    public:
        Manager(const Person &person);
        Manager(const Employee &empl);
        ~Manager();

        int teamSize() const;
        void addEmpl(const int id);
        void ereaseEmply(const int id);

        int salary() const final;
        String job() const final;
        String describe() const final;
    };

private:
    static int _current_id;

private:
    int _id;
    String _name;
    Array<Employee *> _employees;

public:
    Company(const String name);
    Company(const String name, const Array<Employee *> list);
    Company(const Company &other);
    ~Company();


    int size() const;
    int totalSalary() const;
    const Employee *findEmpl(const int id) const;

    // 1 : Manager, 2 : Engineer
    void addEmpl(const Person& person, int job_id);
    void eraseEmpl(const int id);

    friend std::ostream& operator<<(std::ostream& os, const Company& company);

};

inline int Company::_current_id = 10000;
inline int Company::Employee::_current_id = 20000000;
