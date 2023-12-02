// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int getMin(int* p, int from, int to) {
    to++;
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
    
    int c = n;
    for (int i = 0; i < n; i++) {
        int min = getMin(p, 0, participants[i][1]);
        if (min > participants[i][2]) {
            int placeIn2 = participants[i][1];
            int placeIn3 = participants[i][2];
            p[placeIn2] = placeIn3;
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
