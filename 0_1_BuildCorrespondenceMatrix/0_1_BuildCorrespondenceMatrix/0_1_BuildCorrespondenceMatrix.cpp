// 0_1_BuildCorrespondenceMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{   

    int n, m;
    int** matrix;
    ifstream inputFile("input.txt");

    inputFile >> n >> m;
    int a, b;

    matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        inputFile >> a >> b;
        matrix[a - 1][b - 1] = 1;
        matrix[b - 1][a - 1] = 1;
    }

    inputFile.close();

    ofstream outputFile("output.txt");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            outputFile << matrix[i][j] << " ";
        outputFile << endl;
    }
        

}
