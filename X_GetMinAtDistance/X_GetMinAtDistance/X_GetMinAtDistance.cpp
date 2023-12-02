// X_GetMinAtDistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

struct BlockStruct {
    int* pBlocks;
    int* p;
    int blockSize;
    int blockAmount;

    BlockStruct(int* p, int n) {
        this->p = p;
        pBlocks = new int[n];
        blockSize = sqrt(n);
        blockAmount = ceil(n / (double)blockSize);
    }

    int getMinAtArray(int l, int r) {
        int min = p[l];
        for (int i = l + 1; i < r; i++)
            if (p[i] < min)
                min = p[i];

        return min;
    }

    void modifyMin(int modifyIndex, int newValue) {
        int blockIndex = modifyIndex / blockSize;
        p[modifyIndex] = newValue;
        if (pBlocks[blockIndex] > newValue) {
            //for (int i =)
        }
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

    cout << bs.getMinAtArray(0, 2);
}
