// 0_2_CanonicalMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{   
    int n;
    int* arr;
    int a, b;
    ifstream inputFile("input.txt");

    inputFile >> n;

    arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = 0;

    for (int i = 0; i < n; i++) {
        inputFile >> a >> b;
        arr[b - 1] = a;
    }

    inputFile.close();

    ofstream outputFile("output.txt");
    for (int i = 0; i < n; i++)
        outputFile << arr[i] << " ";

    outputFile.close();
}

