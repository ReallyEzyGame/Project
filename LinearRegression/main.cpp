#include "lib.h"
#include "Matrix.h"
#include "specify_vector.h"

#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
// A is the  Matrix  has  the  size of  mxn
// b is the Matrix has the  size of mx1
Matrix PseudoInverse(Matrix A, Matrix &b)
{
    int m = A.row(), n = A.column();
    int minimum = min(m - 1, n);

    vector<Matrix> chainMat;
    Matrix R = A;
    for (int k = 0; k < minimum; ++k)
    {
        // Get the row need to be Reflected
        Matrix x(n - k, 1);
        for (int i = k; i < minimum; ++i)
            x[i][0] = A[k][i];

        // Get the  Vector  for Householder reflect
        double a = -1.0 * signnum(x[1][0]) * EuclidLen(x);
        Matrix e(n - k, 1);
        e[1][0] = 1;
        Matrix v = x + a * e;

        // Householder reflect
        Matrix Hk = HouseHolderMatrix(v);
        // Copy the subMatrx of R
        Matrix subMat(m - k, n - k);
        for (int r1 = k; r1 < m; ++r1)
            for (int c1 = k; c1 < n; ++c1)
                R[r1 - k][c1 - k] = subMat[r1][c1];
        // Update the subMatrix
        Matrix mulMat = Hk * subMat;
        for (int r1 = k; r1 < m; ++r1)
            for (int c1 = k; c1 < n; ++c1)
                R[r1][c1] = mulMat[r1 - k][c1 - k];

        chainMat.push_back(Hk);
    }
    // R = Q^t * A = Hp...H2*H1 * A
    Matrix Q = chainMat[0]; // Q = H1 * H2...*Hp
    for (int i = 1; i < chainMat.size(); ++i)
        Q = Q * chainMat[i];
    if (A.determinant() != 0)
        return R.inverse() * Q.Transpose();
    else
    {
        for (int r = 0; r < m; ++r)
        {
            if (R.rowOfZero(r))
            {
                R = R.excludeRow(r);
                Q = Q.excludeRow(r);
                b = b.excludeRow(r);
                r--;
            }
        }
        return R.inverse() * Q.Transpose();
    }
}
Matrix LinearRegression(Matrix X, Matrix Y)
{
    Matrix mulMat = X * X.Transpose();
    if (mulMat.determinant() == 0)
        return PseudoInverse(mulMat, Y) * X * Y;
    else
        return mulMat.inverse() * X * Y;
}

// Randomly generate data
vector<vector<double>> generatorRandom(const double lowerBound, const double upperBound, int n, int num_var)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(lowerBound, upperBound);

    cout << fixed << setprecision(6);

    vector<vector<double>> random_data;
    while (random_data.size() < n)
    {
        vector<double> test;
        for (int i = 0; i < num_var; ++i)
            test.push_back(distrib(gen));
        random_data.push_back(test);
    }
    return random_data;
}
// Using the data from the file
vector<vector<double>> useFile(string name, int num_var)
{
    ifstream input(name);
    if (!input.is_open())
        return {};

    vector<vector<double>> data;
    // Get  the ordered input
    while (true)
    {
        vector<double> test;
        for (int i = 1; i <= num_var; ++i)
        {
            double val;
            input >> val;
            test.push_back(val);
        }
        if (input.eof())
            break;
        data.push_back(test);
    }
    input.close();
    return data;
}

int main()
{

    vector<vector<double>> data;

    cout << "- Using Mode:\n1. File\n2. RandomGenerator\n";

    int choice;
    cin >> choice;
    cout << "Number variable: ";
    int num_var;
    cin >> num_var;
    num_var++;
    if (choice == 1)
    {
        cout << "- Input the File name: ";
        string name;
        cin >> name;
        data = useFile(name, num_var);
    }
    else if (choice == 2)
    {
        double lower, upper;
        int size;
        cout << "- Generate Data Randomly\n* Choose lower Bound: ";
        cin >> lower;
        cout << "\n* Choose upper Bound: ";
        cin >> upper;
        cout << "\n* Choose size: ";
        cin >> size;
        if (size <= 0)
        {
            cout << "Invalid Size\n Exit\n";
            return 0;
        }
        data = generatorRandom(lower, upper, size, num_var);
    }
    else
    {
        cout << "Exit the  Programm\n";
        return 0;
    }

    // fill the  Matrix
    Matrix X(num_var, data.size());
    Matrix Y(data.size(), 1);
    for (int c = 0; c < X.column(); ++c)
    {
        for (int r = 0; r < X.row() - 1; ++r)
            X[r][c] = data[c][r];

        X[X.row() - 1][c] = 1;
        Y[c][0] = data[c].back();
    }
    // Output radom data testing
    ofstream output("output.csv");
    for (vector<double> list : data)
    {
        for (double val : list)
            output << val << ",";
        output << endl;
    }
    // Result
    Matrix W = LinearRegression(X, Y);
    output << endl << W << endl;
    cout << W << endl;

    output.close();
    return 0;
}