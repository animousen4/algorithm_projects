// 0_0_BinSearch.cpp : Defines the entry point for the application.
//

#include "0_0_BinSearch.h"
#include <iostream>
#include <fstream>
class Solution {
    int lowerBound(int* numbers, int size, int x) {
        int q = 0;
        int r = size;
        int k;
        while (q < r) {
            k = (r + q) / 2;
            if (x <= numbers[k]) {
                r = k;
            }
            else {
                q = k + 1;
            }
        }

        return q;
    }

    int upperBound(int* numbers, int size, int x) {
        int q = 0;
        int r = size;
        int k;
        while (q < r) {
            k = (r + q) / 2;
            if (x < numbers[k]) {
                r = k;
            }
            else {
                q = k + 1;
            }
        }

        return q;
    }

    bool exists(int* numbers, int size, int x) {
        int q = 0;
        int r = size;
        int k;
        while (q < r) {
            k = (q + r) / 2;
            if (x == numbers[k]) {
                return true;
            }
            else if (x < numbers[k]) {
                r = k;
            }
            else if (x > numbers[k]) {
                q = k + 1;
            }
        }

        return false;
    }
public:
    void solve() {
        int numbersAmount;
        int queriesAmount;
        int* numbers = nullptr;
        int* queries = nullptr;

        std::cin >> numbersAmount;
        numbers = new int[numbersAmount];

        for (int i = 0; i < numbersAmount; i++)
            std::cin >> numbers[i];
        std::cin >> queriesAmount;

        queries = new int[queriesAmount];
        for (int i = 0; i < queriesAmount; i++)
            std::cin >> queries[i];

        int x;

        for (int i = 0; i < queriesAmount; i++) {
            x = queries[i];
            std::cout << exists(numbers, numbersAmount, x) << " " << lowerBound(numbers, numbersAmount, x) << " " << upperBound(numbers, numbersAmount, x) << std::endl;
        }
    }
};

int main()
{
    Solution s;
    s.solve();

    return 0;

}

