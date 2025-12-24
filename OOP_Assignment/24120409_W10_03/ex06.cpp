#include <math.h>
#include <iostream>
#include <exception>
#include <sstream>
#include <string.h>
#include <string>

using namespace std;

class CA
{
private:
    double _value;

public:
    CA(const double &v)
    {
        _value = v;
    }
    // Demonstration for crashing
    double GetTest()
    {
        return this->_value;
    }
};

class MyException : public runtime_error
{
private:
    string _errorDescription;
    int _errorCode;

public:
    MyException(const int &errCode, const string &errDes) : runtime_error(BuildErrorMessage(errCode, errDes))
    {
        _errorCode = errCode;
        _errorDescription = errDes;
    }

    const string &GetErrorDiscription()
    {
        return _errorDescription;
    }
    const int &GetErrorCode()
    {
        return _errorCode;
    }

private:
    static const char *BuildErrorMessage(const int &errCode, const string &errDes)
    {
        ostringstream oss;

        oss << "Error code: " << errCode;
        oss << " - Description: " << errDes;

        int len = strlen(oss.str().c_str());
        char *temp = new char[len + 1];
        strcpy_s(temp, len + 1, oss.str().c_str());
        
        return temp;
    }
};

class Level1
{
public:
    static double RunTest4(CA *pCA)
    {
        if (pCA == nullptr)
        {
            throw MyException(123, "Argument must not be null");
        }

        double rs = pCA->GetTest();
        return sqrt(rs);
    }
};

class Level2
{
public:
    static double RunTest3()
    {
        CA *pCA = nullptr;
        double dRS = Level1::RunTest4(pCA);
        return sqrt(dRS);
    }
    static void RunErr()
    {
        throw runtime_error("Common Error");
    }
};

int main()
{
    for (int i = 0; i < 2; i++)
    {
        cout << "*******************************************" << endl;
        try
        {
            if (i == 0)
            {
                cout << Level2::RunTest3() << endl;
            }
            else
            {
                Level2::RunErr();
            }
        }
        catch (const MyException &me)
        {
            cout << "custom error: " << me.what() << endl;
        }
        catch (const exception &ex)
        {
            cout << "common error: " << ex.what() << endl;
        }
    }

    system("pause");
    return 0;
}