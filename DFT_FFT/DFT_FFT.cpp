#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class complex
{
private:
    double real, imaginary;

public:
    complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    ~complex() = default;

    void assign(double r, double i)
    {
        real = r;
        imaginary = i;
    }
    complex get_number() { return complex(real, imaginary); }
    complex get_conjugate() { return complex(real, -imaginary); }

    complex &operator=(const complex &_other)
    {
        // 1. Kiểm tra tự gán (ví dụ: c1 = c1) để tránh lỗi không cần thiết
        if (this == &_other)
        {
            return *this;
        }

        // 2. Gán giá trị từ _other cho đối tượng hiện tại
        this->real = _other.real;
        this->imaginary = _other.imaginary;

        // 3. Trả về một tham chiếu đến đối tượng hiện tại
        return *this;
    }
    complex operator+(complex &_other) const
    {
        return complex(real + _other.real, imaginary + _other.imaginary);
    }
    complex operator-(complex &_other) const
    {
        return complex(real - _other.real, imaginary - _other.imaginary);
    }
    complex operator*(complex &_other) const
    {
        double new_real = real * _other.real - imaginary * _other.imaginary;
        double new_imaginary = real * _other.imaginary + imaginary * _other.real;

        return complex(new_real, new_imaginary);
    }
    complex operator/(const complex &_other) const // Nên thêm const
    {
        double denominator = _other.real * _other.real + _other.imaginary * _other.imaginary;

        // Tránh chia cho 0
        if (denominator == 0)
        {
            // Có thể in lỗi hoặc xử lý theo cách khác
            return complex(NAN, NAN); // Trả về Not-a-Number
        }

        double new_real = (real * _other.real + imaginary * _other.imaginary) / denominator;
        double new_imaginary = (imaginary * _other.real - real * _other.imaginary) / denominator;

        return complex(new_real, new_imaginary);
    }

    complex operator*(double &_other)
    {
        return complex(_other * real, _other * imaginary);
    }
    friend complex operator*(const double &, complex &);

    double module() const { return sqrt(real * real + imaginary * imaginary); }
    double Real() const { return real; }
    double Imaginary() const { return imaginary; }
};

complex operator*(const double &_other, complex &number)
{
    return complex(_other * number.real, _other * number.imaginary);
}

vector<complex> Discrete_Fouried_Transform(vector<double> points)
{
    vector<complex> frequencies;
    int N = points.size();
    for (int k = 0; k <= N - 1; ++k)
    {
        complex sum(0, 0);
        for (int n = 0; n <= N - 1; ++n)
        {
            double angle = 2.0 * M_PI * k * n / N;
            complex number(cos(angle), -sin(angle));
            complex tmp = points[n] * number;
            sum = sum + tmp;
        }
        frequencies.push_back(sum);
    }

    return frequencies;
}

vector<complex> ditFFT2(const double *Ptr, const int N, const int s = 1)
{
    // Base Case
    if (N == 1)
        return {complex(*Ptr, 0)};

    vector<complex> half_low = ditFFT2(Ptr, N / 2, 2 * s);      // DFS on p, p2s,p4s,... p(N-2)s
    vector<complex> half_high = ditFFT2(Ptr + s, N / 2, 2 * s); // DFS on ps, p3s, p5s,... p(N-1)s

    vector<complex> frequencies(N);
    for (int k = 0; k < N / 2; ++k)
    {
        double angle = 2.0 * M_PI * k / N;
        complex p = half_low[k];
        complex q = {cos(angle), -sin(angle)};
        q = q * half_high[k];

        frequencies[k] = p + q;
        frequencies[k + N / 2] = p - q;
    }
    return frequencies;
}

vector<complex> ditFFT(vector<double> points)
{
    if (points.size() & (points.size() - 1) != 0)
    {
        cout << "Error: N must the be a Power of 2\n";
        while (ceil(log2(points.size() ) != floor(log2(points.size()))))
            points.push_back(0);
    }
    return ditFFT2(points.data(), points.size(), 1);
}
int main()
{
    vector<double> input = {1, 2, 3,   0};

    cout << "Using Fast Fourier Transform\n";
    vector<complex> fre = ditFFT(input);
    for (complex f : fre)
        cout << f.Real() << " + " << f.Imaginary() << "i" << endl;
    cout << endl;

    fre = Discrete_Fouried_Transform(input);
    cout << "Using Discrete Fourier Transform\n";
    cout << endl;
    for (complex f : fre)
        cout << f.Real() << " + " << f.Imaginary() << "i" << endl;
}