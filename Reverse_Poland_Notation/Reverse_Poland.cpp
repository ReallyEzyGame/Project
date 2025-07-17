#include <iostream>
#include <string>
using namespace std;

template <typename T>
class stack
{
private:
    T *data;
    int size, capacity;

public:
    stack();
    ~stack();
    bool isEmpty();

    T top();

    void push(const T);
    void pop();
    int stack_size();

private:
    void resize();
};

template <typename T>
stack<T>::stack()
{
    capacity = 1024;
    size = 0;
    data = new T[1024];
}
template <typename T>
stack<T>::~stack()
{
    if (data == nullptr)
        return;
    delete[] data;
    data = nullptr;
}

template <typename T>
bool stack<T>::isEmpty()
{
    if (size == 0)
        return true;
    return false;
}
template <typename T>
T stack<T>::top()
{
    if (size == 0)
        return T{};
    return data[size - 1];
}
template <typename T>
void stack<T>::push(const T key)
{
    if (size == capacity)
        resize();
    if (size == capacity)
        return; // Bad Alloc

    data[size] = key;
    ++size;
}
template <typename T>
void stack<T>::pop()
{
    if (isEmpty())
        return;
    --size;
    data[size] = T{};
}
template <typename T>
int stack<T>::stack_size() { return size; }
template <typename T>
void stack<T>::resize()
{
    T *container = new T[2 * capacity];
    if (container == nullptr)
        return; // Bad Alloc

    capacity *= 2;
    for (int i = 0; i < size; ++i)
        container[i] = data[i];

    delete[] data;
    data = container;
}

bool isoperator(const char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

float to_float(const string str)
{
    int int_part = 0;
    float decimal_part = 0;

    int idx = 0;
    while (idx < str.size() && isdigit(str[idx]))
    {
        int_part = int_part * 10 + (str[idx] - '0');
        ++idx;
    }

    idx = str.size() - 1;
    while (idx >= 0 && isdigit(str[idx]))
    {
        decimal_part = decimal_part / 10.0 + (str[idx] - '0');
        --idx;
    }
    decimal_part /= 10.0;

    return int_part + decimal_part;
}
int precedence(const char oper)
{
    switch (oper)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        cout << "Invalid Argument " << oper << " Detected\n";
        throw(100);
    }
}
string ReversePoland(string str)
{
    string rvs_poland;
    stack<char> stk_oper;

    for (int idx = 0; idx < str.size();)
    {
        // Handle Digit & '.'
        if (isdigit(str[idx]) || str[idx] == '.')
        {
            while (idx < str.size() && (isdigit(str[idx]) || str[idx] == '.'))
                rvs_poland.push_back(str[idx++]);

            rvs_poland.push_back(' ');
        }
        // Handle Operator
        else
        {
            char oper = str[idx++];
            switch (oper)
            {
            case '(':
                stk_oper.push(oper);
                break;
            case ')':
                while (stk_oper.top() != '(')
                {
                    rvs_poland.push_back(stk_oper.top());
                    rvs_poland.push_back(' ');
                    stk_oper.pop();
                }

                stk_oper.pop(); // pop operator '(' out
                if (!stk_oper.isEmpty())
                {
                    rvs_poland.push_back(stk_oper.top());
                    rvs_poland.push_back(' ');

                    stk_oper.pop();
                }
                break;
            default:
                int prio = precedence(oper);
                int prv_prio = -1;
                if (!stk_oper.isEmpty() && stk_oper.top() != '(')
                    prv_prio = precedence(stk_oper.top());

                if (prv_prio <= prio)
                    stk_oper.push(oper);
                else
                {
                    rvs_poland.push_back(stk_oper.top());
                    rvs_poland.push_back(' ');

                    stk_oper.pop();
                    stk_oper.push(oper);
                }
                break;
            }
        }
    }
    while (!stk_oper.isEmpty())
    {
        rvs_poland.push_back(stk_oper.top());
        rvs_poland.push_back(' ');

        stk_oper.pop();
    }
    return rvs_poland;
}
int main()
{
    string infix = "1.25*(1+2*3)/(5+(1+3*4))";
    cout << ReversePoland(infix) << endl;
}