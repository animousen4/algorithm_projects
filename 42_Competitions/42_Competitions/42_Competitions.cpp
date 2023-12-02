// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
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

        for (int i = 0; i < blockAmount; i++)
            pBlocks[i] = INT_MAX;
        

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
        int min = INT_MAX;
        for (int i = l; i < r; i++)
            if (p[i] < min)
                min = p[i];

        return min;
    }

};

int getMin(int* p, int from, int to) {
    int min = p[from];
    for (int i = from + 1; i < to; i++)
        if (min > p[i])
            min = p[i];

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

    BlockStruct bs(p, n);

    int c = n;
    for (int i = 0; i < n; i++) {
        int min = bs.getMin(0, participants[i][1] + 1);
        if (min > participants[i][2]) {
            int placeIn2 = participants[i][1];
            int placeIn3 = participants[i][2];
            bs.modifyMin(placeIn2, placeIn3);
        }
        else 
            c--;

        for (int j = 0; j < n; j++)
            cout << p[j] << "\t";
        cout << endl;
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
