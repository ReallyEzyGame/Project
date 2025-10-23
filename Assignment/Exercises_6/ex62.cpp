#include "stdio.h"

template <typename T>
class Array;
class Cinema;
class Screen;
class Service; // the current Class only focus on the VIPScreens class

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
                data[i] = T();
        }
    }
    Array(const T *, const int);
    Array(const Array<T> &arr) : size(arr.size), capacity(arr.capacity)
    {
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = arr.data[i];
    }
    Array(const int n, const T val) : data(nullptr) {
        data = new T[n];
        if (!data) {
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

    int getSize()
    {
        return size;
    }
    bool empty()
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
    T &operator[](const int idx)
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




// Contains Attribute: standard screen, VIP screen, additional charge base on percentage
//
class Cinema
{
private:
    Array<Screen *> screens;

};

// this is the first version of the screen class: it can only have all row(s) have the same number seat
class Screen
{
protected:
    static int ID;
    int seat_left, seat_booked;
    int seat_price;

    Array<Array<bool>> seats;

public:
    Screen() : seat_left(0), seat_booked(0), seat_price(0), seats(0, 0) {}
    Screen(int row, int column, int seat_price = 0)
    {
        // Should have the Error check here
        row = row > 0 ? row : 0;
        column = column > 0 ? column : 0;
        seat_price = seat_price > 0 ? seat_price : 0;

        if (row > 0 && column > 0)
        {
            seats = Array<Array<bool>>(row, Array<bool>(column));
        }
    };
    Screen(const Screen &);

    void displayAvailableSeat() {
        // display the row number
        for (int i =  0; i < seats.getSize(); ++i)
            printf("%-3d\t", i);
        printf("\n\n");
        // display column and empty/booked seat(s)
        for (int r = 0; r < seats.getSize(); ++r) {

            printf("%d:\t", r);
            for (int c = 0; c < seats[r].getSize(); ++c) {
                if (isSeatAvailable(r,c))
                    printf("X\t");
                else
                    printf("O\t");
            }
            printf("\n");
        }
    }
    // Check is the Seat is empty or not
    bool isSeatAvailable(const int row, const int column)
    {
        return !seats[row][column];
    }
    // this function can be develop later on to call for the bank application, using pay-pal
    // input from keyboard: seat idx(row, column), agree for price
    bool bookSeat()
    {
        int row, column;
        int book;
        printf("Input seat's row & column: ");
        scanf("%d %d", &row, &column);

        if (!isSeatAvailable(row, column))
        {
            printf("+ The Seat has been Occupied\n\tPlease choose other Seat\n");
            return false;
        }

        printf("Do you want to book Seat %d %d\n\t1. Yes\n\t2. No", row, column);
        scanf("%d", &book);

        if (book == 1)
        {
            seats[row][column] = 1;
            seat_left--;
            return true;
        }
        else
        {
            printf("Dimiss the Booking Process\n");
            return false;
        }
    }

    virtual int calculateSeatPrice(const int, const int) = 0;
    virtual int calculateRevenu() = 0;
};
int Screen::ID = 0;

// Standard Screen for normal service & seats
class STDScreen : public Screen
{
public:
    STDScreen() : Screen() {}
    STDScreen(const int num_row, const int num_col) : Screen(num_row, num_col) {}
    STDScreen(const STDScreen &std_scr) : Screen()
    {
        seats = std_scr.seats;
        seat_left = std_scr.seat_left;
    }
    ~STDScreen() = default;

    static int getID()
    {
        static int classID = ID++;
        return classID;
    }
    int calculateSeatPrice(const int row, const int column) override
    {
        return seat_price;
    }
    int calculateRevenu() override
    {
        return seat_left * seat_price;
    }
};
// VIP Screen for extra service & better seats
class VIPScreen : public Screen
{
private:
    float charge_rate; // Additional to VIP seats
    Array<Service> services;

public:
    VIPScreen() : charge_rate(0.f) {}
    VIPScreen(const float rate) : charge_rate(rate) {}
    VIPScreen(const Array<Service> arr, float rate) : services(arr), charge_rate(rate) {}
    VIPScreen(const VIPScreen& vipScr) : services(vipScr.services), charge_rate(vipScr.charge_rate) {}


    int calculateSeatPrice(const int row, const int column) override
    {
        return seat_price * (1 + charge_rate);
    }
    int calculateRevenu() override
    {
        return seat_price * seat_price * (1 + charge_rate);
    }
};