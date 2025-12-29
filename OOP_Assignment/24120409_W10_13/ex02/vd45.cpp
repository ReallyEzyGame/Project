// #include <math.h>
// #include <iostream>
// using namespace std;

// class CA {
// private:
//     double _value;
// public:
//     CA(const double& v) {
//         _value = v;
//     }
//     // Demonstration for crashing
//     double GetTest() {
//         return this->_value;
//     }
// };

// class Level1 {
//     public:
//     // demonstration function for running without controling will cause error
//     static double RunTest3(CA* pCA) {
//         if (pCA == nullptr) {
//             // fix this when commit the homework
//             throw runtime_error("Arugument must not be null");
//         }
//         double rs = pCA->GetTest();
//         return sqrt(rs);
//     }
// };

// int main() {
//     cout << Level1::RunTest3(nullptr) << endl;
//     system("pause");
//     return 0;
// }

#include <math.h>
#include <iostream>
using namespace std;

class CA
{
private:
    double _value;

public:
    CA(const double& v)
    {
        _value = v;
    }
    // Demonstration for crashing
    double GetTest()
    {
        return this->_value;
    }
};

class Level1
{
public:
    // demonstration function for running without controling will cause error
    static double RunTest3(CA* pCA)
    {
        if (pCA == nullptr)
        {
            throw runtime_error("Argument must not be nullptr");
        }
        double rs = pCA->GetTest();
        return sqrt(rs);
    }
};
class Level2
{
public:
    // handling error function base on return value
    static double RunTest2()
    {
        CA* pCA = nullptr;
        double dRS = Level1::RunTest3(pCA);
        return sqrt(dRS);
    }
};

int main()
{
    try
    {
        cout << Level2::RunTest2() << endl;
    }
    catch (const exception& ex)
    {
        cout << "errror: " << ex.what() << endl;
    }
    system("pause");
    return 0;
}