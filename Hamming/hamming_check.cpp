#include <iostream>
#include <vector>
#include <cmath>

void hamming_check(const std::vector<bool> &data, bool is_odd_parity = true)
{
    int len = data.size(), k = 0;
    int sum = 0;

    for (int step = pow(2, k); step < len; k++, step = pow(2, k))
    {
        int pos = step, cnt = 0;
        bool bit = false;
        // iterate through bits that current bit manage
        std::cout << "i = " << k << ": ";
        while (pos <= len)
        {
            if (cnt == step)
            {
                cnt = 0;
                pos += step;
            }
            else
            {
                std::cout << pos << " ";
                bit = data[pos - 1] ? !bit : bit;
                pos++;
                cnt++;
            }
        }
        if (bit == is_odd_parity)
        {
            std::cout << "GOOD";
        }
        else
        {
            std::cout << "ERROR";
        }
        std::cout << std::endl;
        sum += bit == is_odd_parity ? 0 : step;
    }

    if (sum == 0)
    {
        std::cout << "No error detected" << std::endl;
    }
    else
    {
        std::cout << "Error at bit: " << sum << std::endl;
    }
}

int main()
{
    std::cout << "Hamming Checksum:\n";
    do
    {
        int len;
        bool parity;
        std::vector<bool> data;

        std::cout << "Input size: ";
        std::cin >> len;
        if (len <= 0)
        {
            break;
        }

        std::cout << "Input bit stream: ";
        for (int i = 0; i < len; ++i)
        {
            bool tmp;
            std::cin >> tmp;
            data.push_back(tmp);
        }

        std::cout << "odd parity check? 0/1: ";
        std::cin >> parity;

        hamming_check(data, parity);
    } while (true);

    system("pause");
}
