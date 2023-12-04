// 0_9_dfs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;
void search(int r, bool* v, int** arr, int& n, int* indexes, int& curIndex) {
    v[r] = true;
    indexes[r] = curIndex;
    curIndex++;

    for (int i = 0; i < n; i++)
        if (arr[r][i] > 0 && !v[i])
            search(i, v, arr, n, indexes, curIndex);
}
int main()
{

    ifstream inputFile("input.txt");
    int n;
    bool* v;
    int** arr;
    int* indexes;
    int curIndex = 1;

    inputFile >> n;

    arr = new int* [n];
    v = new bool[n];
    indexes = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            inputFile >> arr[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        v[i] = false;
        indexes[i] = -1;
    }

    for (int i = 0; i < n; i++)
        if (indexes[i] < 0)
            search(i, v, arr, n, indexes, curIndex);


    ofstream outputFile("output.txt");

    for (int i = 0; i < n; i++)
        outputFile << indexes[i] << " ";

    outputFile.close();

    
}
