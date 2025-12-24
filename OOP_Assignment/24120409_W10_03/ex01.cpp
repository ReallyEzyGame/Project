#include <math.h>
#include <iostream>
using namespace std;

class CA {
private:
    double _value;
public:
    CA(const double& v) {
        _value = v;
    }
    // Demonstration for crashing
    double GetTest() {
        return this->_value;
    }
};

class Level1 {
    public:
    // demonstration function for running without controling will cause error
    static double RunTest1(CA* pCA) {
        double rs = pCA->GetTest();
        return sqrt(rs);
    }
};

int main() {
    cout << Level1::RunTest1(nullptr) << endl;
    system("pause");
    return 0;
}