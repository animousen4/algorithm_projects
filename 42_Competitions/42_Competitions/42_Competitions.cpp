// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
int getMinOnArray(int* arr, int l, int r) {
    int min = arr[l];
    for (int i = l + 1; i < r; i++)
        if (min > arr[i])
            min = arr[i];
    return min;
}
using namespace std;
int getMin(int* p, int& to, int*pBlocks, int &blockSize, int& blockAmount) {
    int leftBorder = 0;
    int rightBorder = (to - 1) / blockSize;

    if (leftBorder == rightBorder) {
        return p[0];
    }
    else {
        int* min3 = new int[3];
        min3[0] = getMinOnArray(p, leftBorder, (leftBorder + 1) * blockSize + 1);
        min3[1] = getMinOnArray(pBlocks, 1, rightBorder + 1);
        min3[2] = getMinOnArray(p, rightBorder * blockSize, rightBorder + 1);

        int min = min3[0];
        for (int i = 1; i < 3; i++)
            if (min3[i] < min)
                min = min3[i];
        return min;
    }

    
}

void modifyBlock(int& indexToModify, int newValue, int* pBlocks, int& blockSize) {
    int toBlockIndex = (indexToModify - 1) / blockSize;
    if (pBlocks[toBlockIndex] > newValue) {
        pBlocks[toBlockIndex] = newValue;
    }
}
int main()
{   

    int n;
    int* sum;
    int** participants;
    ifstream inputFile("input.txt");
    inputFile >> n;

    n = n + 1;
    participants = new int* [n];

    for (int i = 1; i < n; i++) {
        participants[i] = new int[3];
        inputFile >> participants[i][0] >> participants[i][1] >> participants[i][2];
    }
    inputFile.close();

    sort(participants + 1, participants + n, [](int* a, int* b) {
        return a[0] < b[0];
    });

    int* p = new int[n];
    for (int i = 1; i < n; i++) {
        p[i] = INT_MAX;
    }
    
    int blockSize = sqrt(n - 1);
    int blockAmount = ceil((n - 1) / (double)blockSize);
    int* pBlocks = new int[blockAmount];

    for (int i = 0; i < blockAmount; i++)
        pBlocks[i] = INT_MAX;

    int c = n - 1;
    for (int i = 1; i < n; i++) {
        int min = getMin(p, participants[i][1], pBlocks, blockSize, blockAmount);
        if (min > participants[i][2]) {
            int placeIn2 = participants[i][1];
            int placeIn3 = participants[i][2];
            p[placeIn2] = placeIn3;
            modifyBlock(placeIn2, placeIn3, pBlocks, blockSize);
        }
        else c--;
        cout << min << endl;
        for (int i = 1; i < n; i++)
            cout << p[i] << " ";

        cout << endl;
    }

    for (int i = 1; i < n; i++)
        cout << p[i] << " ";

    cout << endl;

    cout << c;

    ofstream outputFile("output.txt");

    outputFile << c;
    
    outputFile.close();

    return 0;

}

/*
5
2 1 5
1 2 4
4 4 3
3 5 1
5 3 2

*/
