// 0_4_CanonicalMatrixByCorrespondenceMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inputFile("input.txt");
    int n;

    //int** matrix;

    inputFile >> n;

    int* sm = new int[n];
    for (int i = 0; i < n; i++)
        sm[i] = 0;
    bool k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> k;
            if (k)
                sm[j] = i + 1;
        }

    }

    ofstream outputFile("output.txt");
    for (int i = 0; i < n; i++)
        outputFile << sm[i] << " ";
}
