// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int getMin(int* p, int from, int to, int*pBlocks, int &blockSize, int& blockAmount) {
    int min = p[from];
    for (int i = from + 1; i <= to; i++)
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

    int c = n - 1;
    for (int i = 1; i < n; i++) {
        int min = getMin(p, 1, participants[i][1]);
        if (min > participants[i][2]) {
            int placeIn2 = participants[i][1];
            int placeIn3 = participants[i][2];
            p[placeIn2] = placeIn3;
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
