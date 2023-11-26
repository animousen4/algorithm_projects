// 0_8_bfs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int main()
{   

    queue<int> q;
    ifstream inputFile("input.txt");
    int n;
    int** arr;
    inputFile >> n;

    arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            inputFile >> arr[i][j];
        }
    }

}
