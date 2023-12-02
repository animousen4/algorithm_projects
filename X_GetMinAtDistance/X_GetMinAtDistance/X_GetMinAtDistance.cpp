// X_GetMinAtDistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

struct BlockStruct {
    int* pBlocks;
    int* p;
    int n;
    int blockSize;
    int blockAmount;

    BlockStruct(int* p, int n) {
        this->p = p;
        this->n = n;
        blockSize = sqrt(n);
        blockAmount = ceil(n / (double)blockSize);
        pBlocks = new int[blockAmount];

        for (int i = 0; i < blockAmount - 1; i++) {
            int min = p[i * blockSize];
            for (int j = i * blockSize + 1; j < (i + 1) * blockSize; j++)
                if (p[j] < min) {
                    min = p[j];
                }
            pBlocks[i] = min;
        }

        int min = p[(blockAmount - 1) * blockSize];
        for (int i = (blockAmount - 1) * blockSize + 1; i < n; i++)
            if (p[i] < min)
                min = p[i];

        pBlocks[blockAmount - 1] = min;
    }

    int getMin(int l, int r) {
        int blockLeft = l / blockSize;
        int blockRight = r / blockSize;

        int min;
        if (blockLeft == blockRight)
            min = getMinAtArray(p, l, r);
        else {
            int min1 = getMinAtArray(p, l, (blockLeft + 1) * blockSize);
            int min2 = getMinAtArray(pBlocks, (blockLeft + 1), blockRight);
            int min3 = getMinAtArray(p, blockRight * blockSize, r);

            min = min1;

            if (min2 < min)
                min = min2;
            if (min3 < min)
                min = min3;
        }

        return min;
    }
    void modifyMin(int modifyIndex, int newValue) {
        int blockIndex = modifyIndex / blockSize;
        p[modifyIndex] = newValue;

        int min;
        if (blockIndex == blockAmount - 1) {
            min = p[(blockAmount - 1) * blockSize];
            for (int i = (blockAmount - 1) * blockSize + 1; i < n; i++)
                if (min > p[i])
                    min = p[i];
        }
        else {
            min = p[blockIndex * blockSize];
            for (int i = blockIndex * blockSize + 1; i < (blockIndex + 1) * blockSize; i++)
                if (min > p[i])
                    min = p[i];
        }
        pBlocks[blockIndex] = min;
        
    }

private:
    int getMinAtArray(int* p, int l, int r) {
        int min = p[l];
        for (int i = l + 1; i < r; i++)
            if (p[i] < min)
                min = p[i];

        return min;
    }

};
int main()
{
    ifstream inputFile("input.txt");
    int n;

    inputFile >> n;

    int* arr = new int[n];

    for (int i = 0; i < n; i++)
        inputFile >> arr[i];

    inputFile.close();

    BlockStruct bs(arr, n);

    for (int i = 0; i < n; i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "-" << "\t";
    }
    cout << endl;

    bs.modifyMin(1, 40);
    bs.modifyMin(0, 40);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;

    cout << bs.getMin(4, 7);
}
