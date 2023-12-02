// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int blockSize;
int blocksAmount;
int* pBlocks;

int getMinInArray(int* arr, int l, int r) {
    int min = arr[l];
    for (int i = l + 1; i < r; i++)
        min = arr[i];
    return min;
}

int getMin(int* p, int from, int to) {

    int min;
    int leftBorderBlock = from / blockSize;
    int rightBorderBlock = to / blockSize;

    if (leftBorderBlock == rightBorderBlock)
        min = getMinInArray(p, from, to);
    else {
        int min1 = getMinInArray(p, from, (leftBorderBlock + 1) * blockSize);
        int min2 = getMinInArray(pBlocks, (leftBorderBlock + 1), rightBorderBlock);
        int min3 = getMinInArray(p, rightBorderBlock * blockSize, to);

        min = min1;

        if (min2 < min)
            min = min2;
        if (min3 < min)
            min = min3;
    }
    return min;
}
int main()
{   

    int n;
    int* sum;
    int** participants;
    ifstream inputFile("input.txt");
    inputFile >> n;
    participants = new int* [n];

    for (int i = 0; i < n; i++) {
        participants[i] = new int[3];
        inputFile >> participants[i][0] >> participants[i][1] >> participants[i][2];
        participants[i][0]--;
        participants[i][1]--;
        participants[i][2]--;
    }
    inputFile.close();

    sort(participants, participants + n, [](int* a, int* b) {
        return a[0] < b[0];
    });

    int* p = new int[n];
    for (int i = 0; i < n; i++) {
        p[i] = INT_MAX;
    } 

    blockSize = sqrt(n);
    blocksAmount = ceil(n / (double)blockSize);
    pBlocks = new int[blocksAmount];

    for (int i = 0; i < blocksAmount; i++)
        pBlocks[i] = INT_MAX;

    int c = n;
    for (int i = 0; i < n; i++) {
        int min = getMin(p, 0, participants[i][1] + 1);
        if (min > participants[i][2]) {
            int placeIn2 = participants[i][1];
            int placeIn3 = participants[i][2];
            p[placeIn2] = placeIn3;
            if (pBlocks[placeIn2 / blockSize] > p[])
            //pBlocks[placeIn2 / blockSize
        }
        else 
            c--;
    }

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
