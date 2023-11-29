// 42_Competitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{   

    int n;
    int* sum;

    ifstream inputFile("input.txt");
    inputFile >> n;

    sum = new int[n];
    int a, b, c;
    for (int i = 0; i < n; i++) {
        inputFile >> a >> b >> c;
        sum[i] = a + b + c;
    }
    inputFile.close();


    std::vector<int> bestPl;
    bestPl.push_back(sum[0]);
    for (int j = 1; j < n; j++) {
        if (sum[j] < bestPl[0])
            bestPl.clear();
        bestPl.push_back(j);

    }

    ofstream outputFile("output.txt");
    outputFile << bestPl.size();
    outputFile.close();

}
