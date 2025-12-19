#include <iostream>
#include <string>

using namespace std;


class PrintConsleDevice {
private:
    ostream* os;
    PrintConsleDevice() {
        os = &cout;
    }
public:
    void Print(const string& s) {
        *os << s;
    }

    static PrintConsleDevice& GetInstace() {
        static PrintConsleDevice instace;
        return instace;
    }
};


int main() {
    PrintConsleDevice print = PrintConsleDevice::GetInstace();

    print.Print("Su dung in lan 1\n");
    
    PrintConsleDevice print2 = PrintConsleDevice::GetInstace();

    print2.Print("Su dung in lan 2\n\n");

    system("pause");
    return 0;
}