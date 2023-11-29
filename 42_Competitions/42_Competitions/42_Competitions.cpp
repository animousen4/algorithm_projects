// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

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
    }
    inputFile.close();


    sort(participants, participants + n, [](int* a, int* b) {
        return a[0] < b[0];
    });

    for (int i = 0; i < n; i++)
        cout << participants[i][0] << " ";

    ofstream outputFile("output.txt");

    
    outputFile.close();

}
