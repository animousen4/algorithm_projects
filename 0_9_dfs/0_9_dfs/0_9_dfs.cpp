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
        if (arr[r][i] > 0 && !v[r])
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

    int globalIndex = 1;
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

    for (int i = 0; i < n; i++)
        v[i] = false;

    search(0, v, arr, n, indexes, curIndex);


    ofstream outputFile("output.txt");

    for (int i = 0; i < n; i++)
        cout << indexes[i] << " ";

    outputFile.close();

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
