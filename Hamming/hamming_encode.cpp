#include <vector>
#include <cmath>
#include <iostream>

std::vector<bool> hamming_encoding(const std::vector<bool> &data, bool is_odd_parity = true)
{
    // calaculate the size of the hamming enconding result
    int len = 0;
    while (pow(2, len) < data.size() + len + 1)
    {
        len++;
    }

    // Transfer orginal data to the correct position
    std::vector<bool> hamming(data.size() + len);
    for (int i = 0; i < len; ++i)
    {
        hamming[pow(2, i) - 1] = 1;
    }
    for (int i = 0, j = 0; i < hamming.size(); ++i)
    {
        if (hamming[i] == 1)
        {
            continue;
        }
        else
        {
            hamming[i] = data[j];
            ++j;
        }
    }
    // calculate hamming enconding value
    // using the odd-parity notation
    for (int i = 0; i < len; ++i)
    {
        int step = pow(2, i);
        int pos = step + 1, cnt = 1;
        bool bit = 0;

        std::cout << "i = " << i << ": ";
        while (pos <= hamming.size())
        {
            if (cnt == step)
            {
                cnt = 0;
                pos += step;
            }
            else
            {
                std::cout << pos << " ";
                bit = hamming[pos - 1] ? !bit : bit;
                pos++;
                cnt++;
            }
        }
        std::cout << std::endl;
        hamming[step - 1] = bit == is_odd_parity ? false : true;
    }
    return hamming;
}

int main()
{
    std::cout << "Hamming Encoding:\n";
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
        std::vector<bool> hamming = hamming_encoding(data, parity);
        for (int i = 0; i < hamming.size(); ++i)
        {
            std::cout << hamming[i] << " ";
        }
        std::cout << std::endl;
    } while (true);

    system("pause");
}
