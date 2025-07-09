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
// Get random data from the given input
vector<pair<double,double>> getRandomdata(vector<pair<double,double>> data) {
    random_device rd;
    mt19937 g1(rd());
    vector<pair<double,double>> random_data;
    // Get the Random Data
    while (random_data.size() < data.size()) {
        int idx1 =(int) g1() % (data.size() - 1);
        int idx2 =(int) g1() % (data.size() - 1);
        random_data.push_back({data[idx1].first, data[idx2].second});
    }
    return random_data;
}
// Randomly generate data
vector<pair<double,double>> generatorRandom(const double lowerBound, const double  upperBound, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(lowerBound, upperBound);

    cout << fixed << setprecision(6);

    vector<pair<double,double>> random_data;
    while (random_data.size() <  n) {
        double x = distrib(gen),y = distrib(gen);
        random_data.push_back({x,y});
    }
    return random_data;
}
// Using the data from the file
vector<pair<double,double>> useFile(string name) {
    ifstream input(name);
    if (!input.is_open()) return {};

    vector<pair<double, double>> data;
    // Get  the ordered input
    while (!input.eof()) {
        double x, y;
        input >> x >> y;
        data.push_back({x,y});
    }

    input.close();
    return data;
}

int main()
{

    vector<pair<double,double>> data;

    cout << "- Using Mode:\n1. File\n2. RandomGenerator\n";
    
    int choice; cin >> choice;
    if (choice ==  1) {
        cout << "- Input the File name: ";
        string name; cin >> name;
        data =  useFile(name);
    }
    else if (choice == 2) {
        double lower,upper;
        int size;
        cout << "- Generate Data Randomly\n* Choose lower Bound: ";
        cin >> lower;
        cout <<  "\n* Choose upper Bound: ";
        cin >> upper;
        cout <<  "\n* Choose size: ";
        cin >> size;
        if (size <= 0) { cout << "Invalid Size\n Exit\n"; return 0;}
        data =  generatorRandom(lower, upper, size);
    }
    else {
        cout << "Exit the  Programm\n";
        return 0;
    }

    // fill the  Matrix
    Matrix X(2, data.size());
    Matrix Y(data.size(), 1);
    for (int i =  0; i < data.size(); ++i) {
        X[0][i] = data[i].first;
        X[1][i] = 1;
        
        Y[i][0] = data[i].second;
    }
    // Output radom data testing
    ofstream output("output.csv");
    for (pair<double, double> d:data)
        output << d.first << "," << d.second <<  endl;
    // Result
    Matrix W = LinearRegression(X,Y);
    cout << W <<  endl;
    output << endl << W << endl;

    output.close();
    return 0;
}