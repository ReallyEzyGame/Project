#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>

using namespace std;

class RationalSieve {
private:
    struct Relation {
        int x;                    // Giá trị x
        int y;                    // Giá trị y = x + n
        vector<int> x_factors;    // Vector mũ của x
        vector<int> y_factors;    // Vector mũ của y
        vector<int> combined;     // Vector hiệu (x_factors - y_factors) mod 2
        
        Relation(int _x, int _y, vector<int> _xf, vector<int> _yf) 
            : x(_x), y(_y), x_factors(_xf), y_factors(_yf) {
            combined.resize(_xf.size());
            for (int i = 0; i < _xf.size(); i++) {
                combined[i] = (_xf[i] - _yf[i] + 2) % 2; // Đảm bảo không âm
            }
        }
    };
    
    int n;                       // Số cần phân tích
    int smooth_bound;            // Bound B cho smooth numbers
    vector<int> prime_base;      // Factor base (các số nguyên tố)
    vector<Relation> relations;  // Các relations đã tìm được
    
public:
    RationalSieve(int number) : n(number) {
        smooth_bound = calculateSmoothBound();
        prime_base = generatePrimeBase();
    }
    
    // Tính smooth bound theo công thức tối ưu
    int calculateSmoothBound() {
        if (n < 100) return 10;
        double log_n = log(n);
        double log_log_n = log(log_n);
        return sqrt(n);
    }
    
    // Tạo factor base bằng sàng Eratosthenes
    vector<int> generatePrimeBase() {
        vector<bool> is_prime(smooth_bound + 1, true);
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i * i <= smooth_bound; i++) {
            if (is_prime[i]) {
                for (int j = i * i; j <= smooth_bound; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        vector<int> primes;
        for (int i = 2; i <= smooth_bound; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    
    // Phân tích một số thành các thừa số trong factor base
    pair<bool, vector<int>> factorize(int num) {
        vector<int> exponents(prime_base.size(), 0);
        int remaining = abs(num);
        
        for (int i = 0; i < prime_base.size(); i++) {
            while (remaining % prime_base[i] == 0) {
                exponents[i]++;
                remaining /= prime_base[i];
            }
        }
        
        bool is_smooth = (remaining == 1);
        return {is_smooth, exponents};
    }
    
    // Thu thập relations
    void collectRelations() {
    cout << "collet Relation factor base size = " << prime_base.size() << endl;
    cout << "Bound B = " << smooth_bound << endl;
    cout << "Need at least " << prime_base.size() + 5 << " relations" << endl;

    int x = 1;
    int max_attempts = max(50000, n * 10);  // Tăng đáng kể giới hạn

    while (relations.size() < prime_base.size() + 5  && x < max_attempts) {
        int y = x + n;

        auto [x_smooth, x_factors] = factorize(x);
        auto [y_smooth, y_factors] = factorize(y);

        if (x_smooth && y_smooth) {
            relations.emplace_back(x, y, x_factors, y_factors);

            if (relations.size() % 5 == 0 || relations.size() <= 10) {
                cout << "Relation " << relations.size() << ": "
                     << x << " & " << y << " both smooth" << endl;
            }
        }
        x++;
    }

    cout << "Total found: " << relations.size() << " relations" << endl;
}
    
    // Gaussian elimination trên GF(2)
    vector<vector<int>> findLinearDependencies() {
        if (relations.empty()) return {};
        
        cout << "Gaussian elimination..." << endl;
        
        int rows = relations.size();
        int cols = prime_base.size();
        
        // Tạo ma trận augmented với identity matrix
        vector<vector<int>> matrix(rows, vector<int>(cols + rows, 0));
        
        // Điền ma trận chính
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = relations[i].combined[j];
            }
            matrix[i][cols + i] = 1; // Identity part
        }
        
        // Forward elimination
        int pivot_row = 0;
        for (int col = 0; col < cols && pivot_row < rows; col++) {
            // Tìm pivot
            int pivot = -1;
            for (int row = pivot_row; row < rows; row++) {
                if (matrix[row][col] == 1) {
                    pivot = row;
                    break;
                }
            }
            
            if (pivot == -1) continue;
            
            // Hoán đổi hàng
            if (pivot != pivot_row) {
                swap(matrix[pivot], matrix[pivot_row]);
            }
            
            // Elimination
            for (int row = 0; row < rows; row++) {
                if (row != pivot_row && matrix[row][col] == 1) {
                    for (int c = 0; c < cols + rows; c++) {
                        matrix[row][c] ^= matrix[pivot_row][c];
                    }
                }
            }
            pivot_row++;
        }
        
        // Tìm các hàng null (linear dependencies)
        vector<vector<int>> dependencies;
        for (int row = 0; row < rows; row++) {
            bool is_null = true;
            for (int col = 0; col < cols; col++) {
                if (matrix[row][col] != 0) {
                    is_null = false;
                    break;
                }
            }
            
            if (is_null) {
                vector<int> dependency;
                for (int col = cols; col < cols + rows; col++) {
                    dependency.push_back(matrix[row][col]);
                }
                dependencies.push_back(dependency);
            }
        }
        
        cout << "Found: " << dependencies.size() << " linear dependencies" << endl;
        return dependencies;
    }
    
    // Tính GCD bằng thuật toán Euclidean
    int gcd(int a, int b) {
        a = abs(a); b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Tính a^b mod m
    long long power_mod(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
    
    // Thử tìm factor từ một dependency
    int tryFactor(const vector<int>& dependency) {
        // Tính tích các x và y từ dependency
        long long x_product = 1, y_product = 1;
        vector<int> combined_x_exp(prime_base.size(), 0);
        vector<int> combined_y_exp(prime_base.size(), 0);
        
        for (int i = 0; i < dependency.size(); i++) {
            if (dependency[i] == 1) {
                x_product = (x_product * relations[i].x) % n;
                y_product = (y_product * relations[i].y) % n;
                
                for (int j = 0; j < prime_base.size(); j++) {
                    combined_x_exp[j] += relations[i].x_factors[j];
                    combined_y_exp[j] += relations[i].y_factors[j];
                }
            }
        }
        
        // Tính a và b sao cho a² ≡ b² (mod n)
        long long a_squared = 1, b_squared = 1;
        
        for (int i = 0; i < prime_base.size(); i++) {
            if (combined_x_exp[i] % 2 == 1) {
                a_squared = (a_squared * prime_base[i]) % n;
            }
            if (combined_y_exp[i] % 2 == 1) {
                b_squared = (b_squared * prime_base[i]) % n;
            }
        }
        
        // Thử các GCD
        int factor1 = gcd((int)(x_product + y_product) % n, n);
        int factor2 = gcd((int)(x_product - y_product + n) % n, n);
        
        if (factor1 > 1 && factor1 < n) return factor1;
        if (factor2 > 1 && factor2 < n) return factor2;
        
        return -1; // Không tìm được factor
    }
    
    // Thuật toán chính
    vector<int> factorize() {
        cout << "Start Factorization " << n << endl;
        
        // Các trường hợp đặc biệt
        if (n <= 1) return {n};
        if (n == 2) return {2};
        if (n % 2 == 0) {
            auto factors = RationalSieve(n / 2).factorize();
            factors.insert(factors.begin(), 2);
            return factors;
        }
        
        // Kiểm tra số nguyên tố nhỏ
        bool is_prime = true;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            cout << " " << n << " is Prime" << endl;
            return {n};
        }
        
        collectRelations();
        
        if (relations.empty()) {
            cout << "No Relations was found" << endl;
            return {n};
        }
        
        auto dependencies = findLinearDependencies();
        
        if (dependencies.empty()) {
            cout << "No Linear Dependency was Found" << endl;
            return {n};
        }
        
        cout << "Try to find a factor" << endl;
        
        for (const auto& dep : dependencies) {
            int factor = tryFactor(dep);
            if (factor > 1 && factor < n) {
                cout << "Found a factor: " << factor << endl;
                
                // Phân tích đệ quy
                auto factors1 = RationalSieve(factor).factorize();
                auto factors2 = RationalSieve(n / factor).factorize();
                
                factors1.insert(factors1.end(), factors2.begin(), factors2.end());
                sort(factors1.begin(), factors1.end());
                return factors1;
            }
        }
        
        cout << "Trivial Factor" << endl;
        return {n};
    }
    
    // In thông tin debug
    void printDebugInfo() {
        cout << "\nDEBUG Information:" << endl;
        cout << "Number to factor: " << n << endl;
        cout << "Smooth bound: " << smooth_bound << endl;
        cout << "Prime base size: " << prime_base.size() << endl;
        cout << "Prime base: ";
        for (int i = 0; i < min(10, (int)prime_base.size()); i++) {
            cout << prime_base[i] << " ";
        }
        if (prime_base.size() > 10) cout << "...";
        cout << endl;
        cout << "Relations found: " << relations.size() << endl;
    }
};

// Hàm kiểm tra kết quả
bool verifyFactorization(int n, const vector<int>& factors) {
    long long product = 1;
    for (int f : factors) {
        product *= f;
        if (product > n) return false;
    }
    return product == n;
}

// Hàm in kết quả đẹp
void printResult(int n, const vector<int>& factors) {
    cout << "\nResult: " << n << " = ";
    for (int i = 0; i < factors.size(); i++) {
        if (i > 0) cout << " x ";
        cout << factors[i];
    }
    cout << endl;
    
    if (verifyFactorization(n, factors)) {
        cout << "Corret Answer!" << endl;
    } else {
        cout << "Wrong answer!" << endl;
    }
}

int main() {
    cout << "🔐 RATIONAL SIEVE FACTORIZATION ALGORITHM" << endl;
    cout << "=========================================" << endl;
    
    // Test với các số mẫu
    vector<int> test_cases = {15, 21, 35, 77, 91, 143, 187, 221, 323, 391};
    
    cout << "\n🧪 TEST CASES:" << endl;
    for (int num : test_cases) {
        cout << "\n" << string(50, '-') << endl;
        RationalSieve rs(num);
        auto factors = rs.factorize();
        printResult(num, factors);
    }
    
    // Interactive mode
    cout << "\n" << string(50, '=') << endl;
    cout << "🎮 INTERACTIVE MODE" << endl;
    cout << "Input a Positive Interger( 0 to  exit): ";
    
    int n;
    while (cin >> n && n > 0) {
        cout << "\n" << string(50, '-') << endl;
        RationalSieve rs(n);
        
        // Có thể in debug info nếu muốn
        char debug;
        cout << "Debug Information? (y/n): ";
        cin >> debug;
        if (debug == 'y' || debug == 'Y') {
            rs.printDebugInfo();
        }
        
        auto factors = rs.factorize();
        printResult(n, factors);
        
        cout << "\nInput other Int( 0 to exit): ";
    }
    
    cout << "Thanks for using!" << endl;
    return 0;
}