// 0_3_BuildAdjacencyList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{

    int n, m;
    
    ifstream inputFile("input.txt");

    inputFile >> n >> m;
    int a, b;

    vector<vector<int>> matrix(n);

    for (int i = 0; i < m; i++) {
        inputFile >> a >> b;
        matrix[a - 1].push_back(b);
        matrix[b - 1].push_back(a);
    }

    inputFile.close();

    ofstream outputFile("output.txt");
    int kkPointer;
    int* toFill = new int[n];
    for (int i = 0; i < n; i++) {
        
        outputFile << matrix[i].size() << " ";
        for (int m = 0; m < matrix[i].size(); m++)
            outputFile << matrix[i][m] << " ";
        outputFile << endl;
    }

    outputFile.close();

}